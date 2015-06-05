/**
*  \brief     kalman_filter.cpp
*  \details   This file contains kalman_filter class' functions definitions
*  \author    Michal Zakowski
*/
#include <cfloat>
#include <iomanip>      
#include <fstream>

#include "kalman_filter.hpp"

using namespace std;
using namespace commons;

namespace ublas = boost::numeric::ublas;

namespace filter_app {
/**
* Represents measurements time step
*/
const float kalman_filter::PERIOD_=0.1;
/**
* Function invert_matrix
* Inverts square matrix
*/
template<class T>
ublas::matrix<T> kalman_filter::invert_matrix(ublas::matrix<T>& input){
    using namespace ublas;
    matrix<T> inverse=identity_matrix<T> (input.size1());
    typedef permutation_matrix<std::size_t> pmatrix;
    matrix<T> A(input);
    pmatrix pm(A.size1());

    int res = lu_factorize(A, pm);
    inverse.assign(identity_matrix<T>(A.size1()));
    lu_substitute(A, pm, inverse);
    return inverse;
}
/**
* Function print
* Prints matrix
*/
void kalman_filter::print(boost::numeric::ublas::matrix<float>& tmp_matrix){
    cout << endl;
    for (int i = 0; i < tmp_matrix.size1(); i++){
        for (int j = 0; j < tmp_matrix.size2(); j++){
            cout << setprecision(2) << tmp_matrix(i, j) << " ";
        }
        cout << endl;
    }
}
/**
* Function get_current_positions
* Return current positions of all targets
*/
vector<vect3f> kalman_filter::get_current_positions() const{
    std::vector<vect3f> pos;
    for (auto it = targets_.begin(); it != targets_.end(); ++it){
        pos.push_back((*it)->get_current_position());
    }
    return pos;
}
/**
* Function init_targets
* Inits targets in kalman filter by setting states and corresponding process and measurement covariances matrices
* Sets transition and output matrices
*/
void kalman_filter::init_targets(vector<pair<int, vect3f>> positions, std::vector<sensor_parameters_dto> sensor_parameters)
{
    for (auto it = sensor_parameters.begin(); it != sensor_parameters.end(); ++it)
    {
        ublas::matrix<float> tmp = ublas::matrix<float>(6, 6, 0);
        float process_noise = it->process_noise_;
        tmp(0, 0) = tmp(1, 1) = tmp(2, 2) = (PERIOD_*PERIOD_ / 2)*(PERIOD_*PERIOD_ / 2);
        tmp(0, 3) = tmp(1, 4) = tmp(2, 5) = (PERIOD_*PERIOD_*PERIOD_ / 2);
        tmp(3, 0) = tmp(4, 1) = tmp(5, 2) = (PERIOD_*PERIOD_*PERIOD_ / 2);
        tmp(3, 3) = tmp(4, 4) = tmp(5, 5) = PERIOD_*PERIOD_;
        tmp = process_noise*process_noise*tmp;

        float measurement_noise = it->measurement_noise_;
        ublas::matrix<float> tmp2 = measurement_noise*measurement_noise*ublas::identity_matrix<float>(3);

        sensors_.insert(pair<int, shared_ptr<sensor_observer>>(it->id_, shared_ptr<sensor_observer>(new sensor_observer(it->id_, tmp2, tmp))));
    }
    for (auto it2 = positions.begin(); it2 != positions.end(); ++it2)
    {
        ublas::matrix<float> tmp(6, 1, 0);
        tmp(0, 0) = it2->second.x_;
        tmp(1, 0) = it2->second.y_;
        tmp(2, 0) = it2->second.z_;
        targets_.push_back(shared_ptr<target>(new target(it2->first, tmp, sensors_[it2->first]->get_process_covariance())));
    }
    //Prepare matrices used in Kalman Filter equations
    transition_ = ublas::identity_matrix<float>(6);
    transition_(0, 3) = PERIOD_;
    transition_(1, 4) = PERIOD_;
    transition_(2, 5) = PERIOD_;
    output_ = ublas::matrix<float>(3,6,0);
    output_(0, 0) = 1;
    output_(1, 1) = 1;
    output_(2, 2) = 1;
}
/**
* Function compute
* Main kalman filter function. Prepares all calculations and updates targets' states
*/
void kalman_filter::compute(vector<vect3f> new_positions){
    //Comment info: Assume that current state is k+1 and previous state is k
    //Prediction of state k+1 based on historical knowledge
    vector<boost::numeric::ublas::matrix<float> > prediction;

    //Predict k+1 state
    for (auto it = targets_.begin(); it != targets_.end(); ++it)
    {
        prediction.push_back(ublas::prod(transition_, (*it)->get_state()));
    }
    auto target_it = targets_.begin();
    for (auto it = prediction.begin(); it != prediction.end(); ++it, ++target_it)
    {
        //Find closest neighbour in k+1 state measurements
        float min_distance=FLT_MAX;
        vect3f closest_pos;
        for (auto it2 = new_positions.begin(); it2 != new_positions.end(); ++it2)
        {
			vect3f pos((*it)(0, 0), (*it)(1, 0), (*it)(2, 0));
            float dist;
            if ((dist=it2->distance(pos))<min_distance)
            {
                    min_distance=dist;
                    closest_pos=*it2;
            }
        }
        //Calculate Kalman filter equations
        ublas::matrix<float> k_factor(6, 3, 0), tmp_matrix, tmp_matrix2, inversed, meas_matrix;
        
        //update p factor
        tmp_matrix = ublas::prod(transition_, (*target_it)->get_p_factor());

        (*target_it)->set_p_factor(ublas::prod(tmp_matrix, ublas::trans(transition_)) + sensors_[(*target_it)->get_sensor_id()]->get_process_covariance());

        //update kalman factor
        tmp_matrix = ublas::trans(output_);
        k_factor = ublas::prod((*target_it)->get_p_factor(), tmp_matrix);
        tmp_matrix2 = ublas::prod(output_, (*target_it)->get_p_factor());
        tmp_matrix = ublas::prod(tmp_matrix2, tmp_matrix) + sensors_[(*target_it)->get_sensor_id()]->get_measurement_covariance();

        inversed = invert_matrix(tmp_matrix);
        k_factor = ublas::prod(k_factor, inversed);

        //set measurement matrix
        meas_matrix = ublas::matrix<float>(3, 1);
        meas_matrix(0, 0) = closest_pos.x_;
        meas_matrix(1, 0) = closest_pos.y_;
        meas_matrix(2, 0) = closest_pos.z_;

        //update k+1 state by combining k+1 measurement and k+1 prediction
        tmp_matrix = meas_matrix - ublas::prod(output_, (*target_it)->get_state());
        tmp_matrix = targets_[it - prediction.begin()]->get_state() + ublas::prod(k_factor, tmp_matrix);
        (*target_it)->set_state(tmp_matrix);

        //update p factor
        tmp_matrix = ublas::identity_matrix<float>(6) - ublas::prod(k_factor, output_);
        (*target_it)->set_p_factor(ublas::prod(tmp_matrix, (*target_it)->get_p_factor()));
    }
}

} /* namespace filter_app */

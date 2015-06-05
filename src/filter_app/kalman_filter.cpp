/**
*  \brief     kalman_filter.cpp
*  \details   This file contains kalman_filter class' functions definitions
*  \author    Michal Zakowski
*/
#include <cfloat>
#include <iomanip>      
#include "kalman_filter.hpp"
using namespace std;
using namespace filter_app;
namespace ublas = boost::numeric::ublas;
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
void kalman_filter::init_targets(vector<vect3f> positions, vector<pair<float, float> > sensor_noise)
{
    for (auto it = positions.begin(); it != positions.end(); ++it){
        ublas::matrix<float> tmp(6, 1, 0);
        tmp(0, 0) = it->x_;
        tmp(1, 0) = it->y_;
        tmp(2, 0) = it->z_;
        targets_.push_back(shared_ptr<target>(new target(tmp)));

        tmp = ublas::matrix<float>(6, 6, 0);
        float proc_noise = sensor_noise[it - positions.begin()].first;
        tmp(0, 0) = tmp(1, 1) = tmp(2, 2) = (PERIOD_*PERIOD_ / 2)*(PERIOD_*PERIOD_ / 2);
        tmp(0, 3) = tmp(1, 4) = tmp(2, 5) = (PERIOD_*PERIOD_*PERIOD_ / 2);
        tmp(3, 0) = tmp(4, 1) = tmp(5, 2) = (PERIOD_*PERIOD_*PERIOD_ / 2);
        tmp(3, 3) = tmp(4, 4) = tmp(5, 5) = PERIOD_*PERIOD_;
        tmp = proc_noise*proc_noise*tmp;
        p_factors_.push_back(tmp);

        process_covariances_.push_back(tmp);

        float meas_noise = sensor_noise[it - positions.begin()].second;
        tmp = meas_noise*meas_noise*ublas::identity_matrix<float>(3);

        meas_covariances_.push_back(tmp);
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
    for (auto it = prediction.begin(); it != prediction.end(); ++it)
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
        tmp_matrix = ublas::prod(transition_, p_factors_[it - prediction.begin()]);
        p_factors_[it - prediction.begin()] = ublas::prod(tmp_matrix, ublas::trans(transition_)) + process_covariances_[it - prediction.begin()];

        tmp_matrix = ublas::trans(output_);

        //update kalman factor
        k_factor = ublas::prod(p_factors_[it - prediction.begin()], tmp_matrix);
        tmp_matrix = ublas::trans(output_);
        tmp_matrix2 = ublas::prod(output_, p_factors_[it - prediction.begin()]);
        tmp_matrix = ublas::prod(tmp_matrix2, tmp_matrix) + meas_covariances_[it - prediction.begin()];
        inversed = invert_matrix(tmp_matrix);
        k_factor = ublas::prod(k_factor, inversed);

        //set measurement matrix
        meas_matrix = ublas::matrix<float>(3, 1);
        meas_matrix(0, 0) = closest_pos.x_;
        meas_matrix(1, 0) = closest_pos.y_;
        meas_matrix(2, 0) = closest_pos.z_;

        //update k+1 state by combining k+1 measurement and k+1 prediction
        tmp_matrix = meas_matrix - ublas::prod(output_, targets_[it - prediction.begin()]->get_state());
        tmp_matrix = targets_[it - prediction.begin()]->get_state() + ublas::prod(k_factor, tmp_matrix);
        targets_[it - prediction.begin()]->set_state(tmp_matrix);

        //update p factor
        tmp_matrix = ublas::identity_matrix<float>(6) - ublas::prod(k_factor, output_);
        p_factors_[it - prediction.begin()] = ublas::prod(tmp_matrix, p_factors_[it - prediction.begin()]);
    }
}

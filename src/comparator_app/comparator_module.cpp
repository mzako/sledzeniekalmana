/**
 *  \file comparator_module.cpp
 *  \details   This file contains comparator_module class' functions definitions
 *  \author    Adam Mościcki, Jan Kumor
 */

#include "comparator_module.hpp"

#include <iostream>
#include <iterator>
#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include "../commons/cout_writer.hpp"

using namespace std;
using namespace network;
using namespace commons;
using boost::asio::ip::udp;

namespace comparator_app {

std::shared_ptr<comparator_module>  comparator_module::instance_;

void comparator_module::run(shared_ptr<blocking_queue> generator_queue, shared_ptr<blocking_queue> filter_queue)
{
    if(is_started_) {
        get_initial_generator_data(generator_queue);
        //TODO: [JKU] connection needed not UDP
        //send_initial_plot_data();
    }
    /*TODO: [JKU] filter initial messages*/
#ifdef DEBUG
    cout_writer() << "FILTER INIT DATA\n" << filter_queue->pop() << "\nEND DATA\n";
#endif
    int iteration = 0;
    while(is_started_) {
        get_filter_data(filter_queue);
        get_generator_data(generator_queue);
        cout_writer() << "Cumulated eror" << iteration++ << count_error() << "\n";
        send_plot_data();
    }
}

void comparator_module::get_initial_generator_data(shared_ptr<blocking_queue> generator_queue) {
    string g_init_out = generator_queue->pop();
#ifdef DEBUG
    cout_writer() << "GENERATOR INIT DATA\n" << g_init_out << "\nEND DATA\n";
#endif
    stringstream ss(g_init_out);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(sensors_);
    }
}
void comparator_module::get_filter_data(shared_ptr<blocking_queue> filter_queue) {
    string f_out = filter_queue->pop();
#ifdef DEBUG
    cout_writer() << "FILTER DATA:\n" << f_out << "\nEND DATA\n";
#endif
    stringstream ss(f_out);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(filter_output_);
    }
}

void comparator_module::get_generator_data(shared_ptr<blocking_queue> generator_queue) {
    string g_out = generator_queue->pop();
#ifdef DEBUG
    cout_writer() << "GENERATOR DATA:\n" << g_out << "\nEND DATA\n";
#endif
    stringstream ss(g_out);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(positions2_);
        iarchive(measurements_);
    }
}

void comparator_module::send_initial_plot_data() {
    ostringstream plot_stream;
    sensors_plot_string(plot_stream);
#ifdef DEBUG
    cout_writer() << "INITIAL PLOT DATA:\n" << plot_stream.str() << "\nEND DATA\n";
#endif
    send_to_vis(plot_stream.str());
}

void comparator_module::send_plot_data() {
    ostringstream plot_stream;
    sensors_plot_string(plot_stream);
    plot_stream << set_sep_;
    real_plot_string(plot_stream);
    plot_stream << set_sep_;
    meas_plot_string(plot_stream);
    plot_stream << set_sep_;
    track_plot_string(plot_stream);

#ifdef DEBUG
    cout_writer() << "PLOT DATA:\n" << plot_stream.str() << "\nEND DATA\n";
#endif
    send_to_vis(plot_stream.str());
}

void comparator_module::real_plot_string(ostringstream& plot_stream) {
    for( auto it = positions2_.begin(); it != positions2_.end(); ++it) {
        plot_stream << (*it).point_.x_ << sep_ << (*it).point_.y_ << sep_ << (*it).point_.z_;
        if( std::next(it) != positions2_.end() ) {
            plot_stream << line_sep_;
        }
    }
}

void comparator_module::meas_plot_string(ostringstream& plot_stream) {
    bool first = true;
    for( auto it1 = measurements_.begin(); it1 != measurements_.end(); ++it1) {
        auto meas = it1->get_measurements();
        if(meas.size() > 0) {
            for( auto it2 = meas.begin(); it2 != meas.end(); ++it2) {
                if(first) {
                    first = false;
                } else {
                    plot_stream << line_sep_;
                }
                plot_stream << it2->point_.x_ << sep_ << it2->point_.y_ << sep_ << it2->point_.z_;
            }
        }
    }
}

void comparator_module::track_plot_string(ostringstream& plot_stream) {
    for( auto it = filter_output_.begin(); it != filter_output_.end(); ++it) {
        plot_stream << it->x_ << sep_ << it->y_ << sep_ << it->z_;
        if( std::next(it) != filter_output_.end() ) {
            plot_stream << line_sep_;
        }
    }
}

void comparator_module::sensors_plot_string(ostringstream& plot_stream) {
    for (auto it = sensors_.begin(); it != sensors_.end(); ++it) {
        plot_stream << it->radius_ << sep_ << it->position_.x_ << sep_
                << it->position_.y_ << sep_ << it->position_.z_;
        if (std::next(it) != sensors_.end()) {
            plot_stream << line_sep_;
        }
    }
}

void comparator_module::send_to_vis(string data) {
    try {
        boost::asio::io_service io_service;
        udp::resolver resolver(io_service);
        udp::resolver::iterator endpoint = resolver.resolve(
                udp::resolver::query("127.0.0.1", "30001"));
        udp::socket socket(io_service);
        socket.open(udp::v4());
        socket.send_to(boost::asio::buffer(data), *endpoint);
        /*std::array<char, 1> ack;
        socket.receive(boost::asio::buffer(ack));
        if( ack[0] != 0) {
            throw std::runtime_error("No ACK from vis");
        }*/
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
void comparator_module::stop(std::shared_ptr<blocking_queue> compartaor_queue, std::shared_ptr<blocking_queue> filter_queue)
{
    is_started_ = false;
}

double comparator_module::count_error()
{
    /** CHECK THIS OUT JKU **/
    cout_writer() << positions2_.size() << filter_output_.size();
    double error = 0.0f;
    for(auto it = positions2_.begin(); it != positions2_.end(); ++it) { //foreach point in real points
        if(filter_output_.size() > 0) {
            auto closest = filter_output_.begin();
            for(auto itt = filter_output_.begin() + 1; itt != filter_output_.end(); ++itt) { //find the closest
                if (it->point_.distance(*itt) < it->point_.distance(*closest)) {
                    closest = itt;
                }
            }
            error += closest->distance(it->point_);
        }
    }
    return error;
}

} /* namespace comparator_app */

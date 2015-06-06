/**
 *  \brief     filter_module.cpp
 *  \details   This file contains comparator_module class' functions definitions
 *  \author    Adam Mościcki
 */

#include "comparator_module.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include "../commons/cout_writer.hpp"

using namespace std;
using namespace network;
using namespace commons;

namespace comparator_app {

std::shared_ptr<comparator_module>  comparator_module::instance_;

void comparator_module::run(std::shared_ptr<blocking_queue> generator_queue, std::shared_ptr<blocking_queue> filter_queue)
{
    /*TODO: [JKU] initial messages
     * wiadomość z generatora możnaby wykorzystać do narysowaniu zasięgu sensorów
     * wiadomość z filtra??*/
    cout_writer() << filter_queue->pop();
    cout_writer() << generator_queue->pop();
    while(is_started_) {
        string f_out = filter_queue->pop();
#ifdef DEBUG
        cout_writer() << "FILTER DATA:\n" << f_out << "\nEND DATA\n";
#endif
        stringstream ss1(f_out);
        {
            cereal::JSONInputArchive iarchive(ss1);
            iarchive(
                    filter_output_
            );
        }
        string g_out = generator_queue->pop();
#ifdef DEBUG
        cout_writer() << "FILTER DATA:\n" << g_out << "\nEND DATA\n";
#endif
        stringstream ss2(g_out);
        {
            cereal::JSONInputArchive iarchive(ss2);
            iarchive(positions_);
            iarchive(measurements_);
        }
    }

}

void comparator_module::stop(std::shared_ptr<blocking_queue> compartaor_queue, std::shared_ptr<blocking_queue> filter_queue)
{
    is_started_ = false;
}

}

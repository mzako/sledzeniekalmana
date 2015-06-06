/*
 * sensor_dto.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: elohhim
 */

#ifndef _SENSOR_DTO_HPP
#define _SENSOR_DTO_HPP

#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "measurement_dto.hpp"

namespace commons {

struct sensor_dto {
public:
    sensor_dto() {};
    virtual ~sensor_dto() {};

    std::vector<measurement_dto>& get_measurements(){
        return measurements_;
    }
    int get_id() const { return id_; }
    template<class Archive>
    void serialize( Archive& archive) {
        archive(
                cereal::make_nvp("id", id_ ),
                //TODO: [JKU] maybe this should always be nvp target and add field telling about type
                measurements_
        );
    }

private:
    unsigned id_;
    std::vector<measurement_dto> measurements_;
};

} /* namespace commons */

#endif /* _SENSOR_DTO_HPP */

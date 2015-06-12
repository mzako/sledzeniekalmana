/**
 *  \brief     test.cpp
 *  \details   This file contains generator_app test suites
 *  \author    Michal Zakowski
 */
#ifdef TEST

#define BOOST_TEST_MAIN
#include <vector>
#include <boost/test/included/unit_test.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include "curves/balistic.hpp"
#include "curves/line.hpp"
#include "target.hpp"
#include "sensor_observer.hpp"
using namespace boost::unit_test;
using namespace generator_app;
using namespace curves;
using namespace commons;
using namespace std;
/**
 * balistic class unit test
 */
BOOST_AUTO_TEST_CASE(balistic_test)
{
    boost::mt19937 rng;
    boost::uniform_real<float> u(1, 100);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);

    balistic balistic_t(vect3f(0.0, 0.0, 0.0), gen());
    for (float time = 0; time < 100; time += 0.1)
    {
        BOOST_CHECK_MESSAGE(balistic_t.get_position(time).x_ == 0 && balistic_t.get_position(time).z_ == 0, "Zla pozycja dla zerowej predkosci");
    }

    float vx = gen(), vz = gen();
    balistic_t = balistic(vect3f(vx, gen(), vz), 0.0);

    for (float time = 0; time < 100; time += 1.0)
    {
        BOOST_CHECK_MESSAGE(balistic_t.get_position(time).x_ == vx*time && balistic_t.get_position(time).z_ == vz*time, "Zla pozycja dla zerowego oporu powietrza");
    }

    vx = vz = gen();
    balistic_t = balistic(vect3f(vx, gen(), vz), gen());

    for (float time = 0; time < 100; time += 1.0)
    {
        BOOST_CHECK_MESSAGE(balistic_t.get_position(time).x_ == balistic_t.get_position(time).z_, "Zla pozycja dla tych samych vx i vz");
    }
    vx = vz = gen();
    balistic_t = balistic(vect3f(vx, gen(), vz), -gen());

    for (float time = 0; time < 100; time += 1.0)
    {
        BOOST_CHECK_MESSAGE(balistic_t.get_position(time).x_ == vx*time && balistic_t.get_position(time).z_ == vz*time, "Zle zachowanie dla ujemnego oporu");
    }
}
/**
 * line class unit test
 */
BOOST_AUTO_TEST_CASE(line_test)
{
    boost::mt19937 rng;
    boost::uniform_real<float> u(1, 100);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
    line line_t(vect3f(0, 0, 0));

    for (float time = 0; time < 100; time += 0.1)
    {
        BOOST_CHECK_MESSAGE(line_t.get_position(time).x_ == 0 && line_t.get_position(time).y_ == 0 && line_t.get_position(time).z_ == 0, "Zla pozycja dla zerowej predkosci");
    }

    float vx = gen(), vy = gen(),vz = gen();
    line_t = line(vect3f(vx, vy, vz));

    for (float time = 0; time < 100; time += 1.0)
    {
        BOOST_CHECK_MESSAGE(line_t.get_position(time).x_ == vx*time && line_t.get_position(time).y_ == vy*time && line_t.get_position(time).z_ == vz*time, "Zla pozycja");
    }

    vx = vy = vz = gen();
    line_t = line(vect3f(vx, vy, vz));

    for (float time = 0; time < 100; time += 1.0)
    {
        BOOST_CHECK_MESSAGE(line_t.get_position(time).x_ == line_t.get_position(time).z_
                && line_t.get_position(time).x_ == line_t.get_position(time).y_
                && line_t.get_position(time).y_ == line_t.get_position(time).z_
                , "Zla pozycja dla tych samych vx, vy i vz");
    }
}
/**
 * target class unit test
 */
BOOST_AUTO_TEST_CASE(target_test)
{
    for (int i = 1; i < 100; i++)
    {
        target tmp = target();
        BOOST_CHECK_MESSAGE(tmp.get_id()==i, "Zle numerowanie id");

    }
    shared_ptr<curve> line_t(new line(vect3f(1.0, 1.0, 1.0)));
    target target_t(line_t);
    BOOST_CHECK_MESSAGE(target_t.get_initial_position() == vect3f(0, 0, 0), "Zla inicjacja poczatkowej pozycji");
    BOOST_CHECK_MESSAGE(target_t.get_current_position() == vect3f(0, 0, 0), "Zla inicjacja aktualnej pozycji");

    for (float time = 0; time < 100; time += 1.0)
    {
        target_t.update(time);
        BOOST_CHECK_MESSAGE(target_t.get_initial_position() == vect3f(0, 0, 0), "Zmiana pozycji poczatkowej");
        BOOST_CHECK_MESSAGE(target_t.get_current_position() == line_t->get_position(time), "Zla wartosc aktualnej pozycji");
    }
    shared_ptr<curve> curve_t = target_t.get_curve();
    BOOST_CHECK_MESSAGE(curve_t == line_t, "Zly obiekt krzywej");
}
/**
 * sensor_observer class unit test
 */
BOOST_AUTO_TEST_CASE(sensor_observer_test)
{
    for (int i = 1; i < 100; i++)
    {
        sensor_observer tmp = sensor_observer();
        BOOST_CHECK_MESSAGE(tmp.get_id() == i, "Zle numerowanie id");

    }
    sensor_observer sensor_observer_t(vect3f(1.0, 1.0, 1.0), 100.0, 2.0, 2.0);

    BOOST_CHECK_MESSAGE(sensor_observer_t.get_measurement_noise() == 2.0, "Zla inicjacja szumu pomiaru");
    BOOST_CHECK_MESSAGE(sensor_observer_t.get_process_noise() == 2.0, "Zla inicjacja szumu procesu");
}
/**
 * target and sensor_observer classes test
 */
BOOST_AUTO_TEST_CASE(target_sensor_observer_test)
{
    shared_ptr<curve> line_t(new line(vect3f(1.0, 1.0, 1.0)));
    target target_t(line_t);
    sensor_observer sensor_observer_t1(vect3f(0.0, 0.0, 0.0), 10.0, 1.0, 1.0);
    sensor_observer sensor_observer_t2(vect3f(20.0,0.0, 0.0), 10.0, 0.0, 0.0);

    vector<shared_ptr<sensor_observer>> sensor_vec_t;

    sensor_vec_t.push_back(shared_ptr<sensor_observer>(&sensor_observer_t1));
    sensor_vec_t.push_back(shared_ptr<sensor_observer>(&sensor_observer_t2));
    shared_ptr<vector<shared_ptr<sensor_observer>>> p_sensor_vec_t(&sensor_vec_t);

    target_t.set_sensor_observers(p_sensor_vec_t);

    BOOST_CHECK_MESSAGE(sensor_observer_t1.get_measurements().size() == 0, "Zla inicjacja zaszumionych pozycji");
    BOOST_CHECK_MESSAGE(sensor_observer_t1.get_positions().size() == 0, "Zla inicjacja pozycji");
    for (float time = 0; time < 31; time += 1.0)
    {
        target_t.update(time);
        std::vector<commons::measurement_dto> pos1 = sensor_observer_t1.get_measurements();
        std::vector<commons::measurement_dto> pos2 = sensor_observer_t2.get_measurements();
        if (pos1.size())
        {
            //BOOST_CHECK_SMALL(pos1[0].point_.distance(line_t->get_position(time)), (double)1.0);
        }
        if (pos2.size())
        {
            //BOOST_CHECK_SMALL(pos2[0].point_.distance(line_t->get_position(time)), (double)0.0);
        }
        if (time == 10.0)
        {
            BOOST_CHECK_MESSAGE(sensor_observer_t1.get_positions().size() == 1
                    && sensor_observer_t2.get_positions().size() == 1, "Zla aktualizacja pozycji");
        }
    }
    BOOST_CHECK_MESSAGE(sensor_observer_t1.get_positions().size() == 0
            && sensor_observer_t2.get_positions().size() == 0, "Zla aktualizacja pozycji");
}

#endif

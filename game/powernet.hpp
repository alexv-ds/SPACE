#pragma once
#include <limits>
#include <flecs.h>

namespace game {

/*
  //////////
  //ПРИМЕР//
  //////////
  //Контроллер сети
  auto powernet = world.entity()
    .add<Powernet>();

  //Добавить к сети участников можно так:
  //Потребитель
  world.entity()
    .set<Consumer>({.power=10})
    .add<Link>(powernet); //привязываем к сети

  //Источник
  world.entity()
    .set<Producer>({.power=10})
    .add<Link>(powernet);
  
  //Батарейка
  world.entity()
    .set<EnergyStorage>({.max_energy=100})
    .add<Link>(powernet);

*/

struct Powernet {
  // На эти таймеры можно подвязывать системы
  // если нужно синхонизироваться с системами обновления сети
  // Существует различные типы сетей:
  // Медленные - сети в которых есть компонент SlowPowernetUpdate
  // Быстрые - сети в которых есть компонент FastPowernetUpdate, у них нет таймера, срабатывают каждый кадр
  // Обычные - сети без компонентов FastPowernetUpdate и SlowPowernetUpdate рассматриваются как "обычные"
  // От типа сети зависит частота их обновлений и, соответственно, нагрузка на железо
  // Желательно как можно больше сетей держать в "медленном" состоянии. 
  // Однако при необходимости можно менять тип сети на лету
  flecs::entity_t slow_powernet_tick_source; //1 Hz
  flecs::entity_t normal_powernet_tick_source; //5 Hz

  Powernet(flecs::world&);
};

} //namespace game

namespace game::powernet {

struct Powernet {
  //Отражает потребление сети с предыдущего обновления
  float power_consumption = 0; //Watt
  //Отражает генерацию сети с предыдущего обновления
  float power_generation = 0; //Watt

  //internal
  //Каждый потребитель энергии добавляет свое значение потребления каждое обновление сети
  //Если on_frame_power_usage становится больше power_generation, то потребитель и остальные потребители
  //Лишаются компонента Powerized
  float on_frame_power_usage = 0; //Watt
};

//Потребитель энергии, должен быть связан с Powernet, через Link отношение
struct Consumer {
  float power = 0; //Watt
};

//Источник энергии, должен быть связан с Powernet, через Link отношение
struct Producer {
  float power = 0; //Watt
};

//Батарейка, может заряжаться и разряжаться
struct EnergyStorage {
  //Минимальное выходное значение отдачи
  float min_output_power = 0; //Watt
  //Максимальное выходное значение отдачи
  float max_output_power = std::numeric_limits<float>::infinity(); //Watt
  //Максимальное входное значение потребления (ака зарядки)
  //Минимального нет, ибо не имеет смысл
  float input_power = std::numeric_limits<float>::infinity();
  //Запасённая энергия
  //может быть отрицательным. Значит то, что из батарейки взяли больше, чем в ней было, кек
  //Не беда, вселенский балланс востановим когда заряжать будем
  float energy = 0;
  //Максимальная вместимость. Зачастую значение поля energy будет чуть больше чем max_energy
  //Я решил, что лучше так, чем терять какую-то долю энергии
  float max_energy = std::numeric_limits<float>::infinity();

  //internal
  //Положительное если "отдает" от себя, отрицательное если "забирает" 
  float last_update_power = 0;
};

//См пример
struct Link {};

//Появляется на сущности у которой есть компонент Consumer
//При ее отсутствии рассмататривать как отсутствие энергии в сети
struct Powerized {};

//Не устанавливается в системах, однако учитывается при обновлении
//Выключенные участники сети не обновляются, а так же при добавлении
//сущности этого компонента, у нее удаляется компонент Powerized
struct Disabled {};

//Частота обновления сети зависит от наличия этих компонентов у контроллера сети (Powernet)
//SlowPowernetUpdate - медленная частота обновлений
//FastPowernetUpdate - быстрая частота обновлений
//При отсутствии этих двоих компонентов, частота обновлений рассматривается как "нормальная"
struct SlowPowernetUpdate {};
struct FastPowernetUpdate {};

} //namespace game::powernet
#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <functional>
#include <flecs.h>


namespace engine::command {

struct PhaseProcessCommandsPre {};
struct PhaseProcessCommands {};

/**
 * Обработчик комманды. Комманда будет добавлена к первой сущщности по
 * ниспадающей иерархии
 * (Handle, *)
 */
struct Handle {};

/**
 * Обработчик комманды. Так же как и Handle, но в отличии от него комманда не будет
 * добавлена к сущности. Можно использоваться что бы подавить комманду (категорию)
 * (Supress, *)
 *
 * @see Handle
 */
struct Supress {};

/**
 * Испускает комманду
 * (Emit, *)
 */
struct Emit {};

/**
 * Принятая комманда
 * (On, *)
 */
struct On {};

struct ConnectionNext {};
struct ConnectionPrev {};

/**
 * Флаг, вешается на компонент. Характеризует то, что компонент является коммандой.
 */
struct Command {};

/**
 * Категория комманды, вешается на компонент
 * (Category, *)
 */
struct Category {};

} //end of namespace engine::command
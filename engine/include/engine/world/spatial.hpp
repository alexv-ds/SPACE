#pragma once

namespace engine::world {

/**
 * При наличии данного компонента у сущности все другие сущности, которые данная сущность будет
 * пересекать будет установлено отношение (IntersectedWith, *) с ссылкой
 * на сущность у которой есть компонент HandleIntersections
 */
struct HandleIntersections {};
struct IntersectsWith {}; ///Relation

} //end of namespace engine::world
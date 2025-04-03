#include <vector>
#include <memory>

#include <Obj.h>
#include <glm/glm.hpp>

class Scene{

private:
  std::vector<std::unique_ptr<KroozOBJ>> Objects;
  int index;

public:
  Scene();
  void AddObjects(std::unique_ptr<KroozOBJ> obj);
  bool RenderEveryThing(GLuint MatrixLocation);
  const std::vector<std::unique_ptr<KroozOBJ>>& GetObjects() const { return Objects; }
};

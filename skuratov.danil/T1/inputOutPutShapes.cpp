#include "inputOutputShapes.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "diamond.hpp"
#include "parallelogram.hpp"

void skuratov::clearingShapes(Shape** shapes, size_t count)
{
  size_t i = 0;
  while (i < count)
  {
    delete shapes[i];
    ++i;
  }
  delete[] shapes;
}

void skuratov::inputRectangle(std::istream& input, Shape** shapes, size_t& count)
{
  double args[4] = {};
  size_t i = 0;
  while (i < 4)
  {
    input >> args[i];
    if (!input)
    {
      throw std::invalid_argument("Invalid arguments for the Rectangle in input");
    }
    ++i;
  }
  shapes[count] = new Rectangle({ args[0], args[1] }, { args[2], args[3] });
}

void skuratov::outputFrameRec(std::ostream& out, const Shape* shape)
{
  out << " ";
  out << shape->getFrameRect().pos.x - shape->getFrameRect().width / 2 << " ";
  out << shape->getFrameRect().pos.y - shape->getFrameRect().height / 2 << " ";
  out << shape->getFrameRect().pos.x + shape->getFrameRect().width / 2 << " ";
  out << shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
}

void skuratov::inputSquare(std::istream& input, Shape** shapes, size_t& count)
{
  double args[3] = {};
  for (size_t i = 0; i < 3; ++i)
  {
    input >> args[i];
    if (!input)
    {
      throw std::invalid_argument("Invalid arguments for the Square");
    }
    ++i;
  }
  shapes[count] = new Square({ args[0], args[1] }, args[2]);
}

void skuratov::inputDiamond(std::istream& input, Shape** shapes, size_t& count)
{
  double args[6] = {};
  input >> args[0] >> args[1] >> args[2] >> args[3] >> args[4] >> args[5];
  if (!input)
  {
    throw std::invalid_argument("Invalid arguments for the Diamond");
  }
  shapes[count] = new Diamond({ args[0], args[1] }, { args[2], args[3] }, { args[4], args[5] });
}

void skuratov::inputParallelogram(std::istream& input, Shape** shapes, size_t& count)
{
  double args[6] = {};
  size_t i = 0;
  do
  {
    input >> args[i];
    ++i;
  }
  while (i < 6 && input);

  if (!input)
  {
    throw std::invalid_argument("Invalid arguments for the Parallelogram");
  }
  shapes[count] = new Parallelogram({ args[0], args[1] }, { args[2], args[3] }, { args[4], args[5] });
}

skuratov::Shape** skuratov::inputShapes(std::istream& input, size_t& count)
{
  std::string shape = "";
  Shape** newShape = nullptr;
  while (input >> shape && shape != "SCALE")
  {
    try
    {
      Shape** oldShape = newShape;
      newShape = new Shape*[count + 1] {};
      if (oldShape)
      {
        for (size_t i = 0; i < count; ++i)
        {
          newShape[i] = oldShape[i];
        }
      }
      delete[] oldShape;

      if (shape == "RECTANGLE")
      {
        skuratov::inputRectangle(input, newShape, count);
        ++count;
      }
      if (shape == "SQUARE")
      {
        skuratov::inputSquare(input, newShape, count);
        ++count;
      }
      if (shape == "PARALLELOGRAM")
      {
        skuratov::inputParallelogram(input, newShape, count);
        ++count;
      }
      if (shape == "DIAMOND")
      {
        skuratov::inputDiamond(input, newShape, count);
        ++count;
      }
    }
    catch (const std::bad_alloc& e)
    {
      clearingShapes(newShape, count);
      throw;
    }
    catch (const std::logic_error& e)
    {
      std::cerr << e.what() << '\n';
      continue;
    }
    catch (...)
    {
      std::cerr << "error\n";
      continue;
    }
  }
  if (!input)
  {
    clearingShapes(newShape, count);
    throw;
  }
  return newShape;
}

void skuratov::outputShapes(std::ostream& out, Shape* const* shapes, size_t count)
{
  double area = 0;
  for (size_t i = 0; i < count; ++i)
  {
    area += shapes[i]->getArea();
  }
  out << area;
  for (size_t i = 0; i < count; ++i)
  {
    outputFrameRec(out, shapes[i]);
  }
}

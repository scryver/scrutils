template <typename Number>
Vector2D<Number>::Vector2D() :
    Vector2D(0, 0)
{

}

template <typename Number>
Vector2D<Number>::Vector2D(const Number& both) :
    Vector2D(both, both)
{

}

template <typename Number>
Vector2D<Number>::Vector2D(const Number& x_, const Number& y_) :
    x(x_), y(y_)
{
    // Empty
}

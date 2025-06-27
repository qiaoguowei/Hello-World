
class Shape
{
public:
    Shape();
    virtual void boundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* createManipulator() const;
};

class TextView
{
public:
    TextView();
    void getOrigin(Coord& x, Coord& y) const;
    void getExtent(Coord& width, Coord& height) const;
    virtual bool isEmpty() const;
};

class TextShape : public Shape
{
public:
    TextShape(TextView *);
    virtual void boundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* createManipulator() const;
    bool isEmpty() const;

private:
    TextView *_text;
};

TextShape::TextShape(TextView* t)
{
    _text = t;
}

void TextShape::boundingBox(Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;

    _text->getOrigin(bottom, left);
    _text->getExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}

bool TextShape::isEmpty() const
{
    return _text->isEmpty();
}

Manipulator* TextShape::createManipulator() const
{
    return new TextManipulator(this);
}










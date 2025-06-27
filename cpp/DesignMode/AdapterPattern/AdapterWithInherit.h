
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

class TextShape : public Shape, private TextView
{
public:
    TextShape();
    virtual void boundingBox(Point& bottomLeft, Point& topRight) const;
    virtual bool isEmpty() const;
    virtual Manipulator* createManipulator() const;
};

void TextShape::boundingBox(Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;

    getOrigin(bottom, left);
    getExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRigth = Point(bottom + height, left + width);
}

bool TextShape::isEmpty() const
{
    return TextView::isEmpty();
}

Manipulator* TextShape::createManipulator() const
{
    return new TextManipulator(this);
}







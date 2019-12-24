struct vector2d
{
    float x;
    float y;

    vector2d(){}
    vector2d(const float x,const float y):x(x),y(y){}

    bool operator==(const vector2d& vec) const{
        return x == vec.x && y == vec.y;
    } 
};

const vector2d rot(const vector2d vec, const int angle)
{
    const int num_of_90 = angle / 90;

    vector2d ans;

    switch (num_of_90 % 4)
    {
    case 1:
        ans.x = vec.y;
        ans.y = -vec.x;
        break;
    case 2:
        ans.x = -vec.x;
        ans.y = -vec.y;
        break;
    case 3:
        ans.x = -vec.y;
        ans.y = vec.x;
        break;
    default:
        ans.x = vec.x;
        ans.y = vec.y;
        break;
    }

    return ans;
}
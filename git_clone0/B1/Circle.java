package figure;

import static java.lang.Math.PI;

public class Circle {
    double r;//圆的半径
    double l;//圆的周长
    double s;//圆的面积
    double getL()
    {
        System.out.println("圆形的周长为：");
        l=2*PI*r;
        return l;
    }
    double getS()
    {
        System.out.println("圆形的面积为：");
        s=r*r*PI;
        return s;
    }

}

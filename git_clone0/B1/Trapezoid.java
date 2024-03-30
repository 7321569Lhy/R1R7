package figure;

public class Trapezoid {
    double upper_base;//梯形上底
    double lower_base;//梯形下底
    double h;//梯形的高
    double s;//梯形面积

    double getS()
    {
        System.out.println("梯形的面积为：");
        s=(upper_base+lower_base)/2*h;
        return s;
    }
}

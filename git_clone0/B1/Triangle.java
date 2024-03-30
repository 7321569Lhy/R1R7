package figure;

import static java.lang.Math.abs;

public class Triangle {
    double sideA,sideB,sideC;//三角形的三条边
    double l;//三角形周长
    double s;//三角形面积
    double getL(){
        System.out.println("三角形的周长为：");
        l=sideA+sideB+sideC;
        return l;
    }
    double getS(){
        System.out.println("三角形的面积为：");
        double s0=(l/2)*(l/2-sideA)*(l/2-sideB)*(l/2-sideC);
        s=Math.pow(s0,0.5);
        return s;
    }
    void setsides(double a1,double b1,double c1){
        this.sideA=a1;
        this.sideB=b1;
        this.sideC=c1;
    }
    boolean judge(double a2,double b2,double c2){
        if ((a2<b2+c2)&&(a2>abs(c2-b2))){
            return true;
        }
        else{
            System.out.println("无法形成三角形，重新设置三条边");
            return false;
        }
    }
    double getsideA()
    {
        return sideA;
    }
    double getsideB()
    {
        return sideB;
    }
    double getSideC()
    {
        return sideC;
    }
}

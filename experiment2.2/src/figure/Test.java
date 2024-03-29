package figure;

public class Test {
    public  static void main(String[] args){
        Triangle case1=new Triangle();
        Trapezoid case2=new Trapezoid();
        Circle case3=new Circle();
        case1.setsides(3,4,5);
        boolean result=case1.judge(case1.sideA, case1.sideB, case1.sideC);
        if(result){
            double l1=case1.getL();
            System.out.println(l1);
            double s1=case1.getS();
            System.out.println(s1);
        }
        case2.upper_base=3;
        case2.lower_base=8;
        case2.h=4;
        double s2=case2.getS();
        System.out.println(s2);
        case3.r=2;
        double l3=case3.getL();
        System.out.println(l3);
        double s3=case3.getS();
        System.out.println(s3);
    }
}

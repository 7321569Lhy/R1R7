package payment;

public class pay {
    double price;
    double withhold_rate;
    double pay_rate;
    double payment;
    void computePayment(double time,double withhold_rate,double pay_rate){
        double payment=time*price*(1-withhold_rate)*(1-pay_rate);
        System.out.println(payment);
    }
    void computePayment(double time,double pay_rate){
        double payment=time*price*(1-0.15)*(1-pay_rate);
        System.out.println(payment);
    }
    void computePayment(double time){
        double payment=time*price*(1-0.15)*(1-0.0465);
        System.out.println(payment);
    }
}

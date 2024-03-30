package payment;
public class test {
    public static  void main(String[] args){
        pay example=new pay();
        int time=10;
        example.price=24;
        example.withhold_rate=0.10;
        example.pay_rate=0.05;
        example.computePayment(time, example.withhold_rate, example.pay_rate);
        example.computePayment(time, example.pay_rate);
        example.computePayment(time);
    }
}

import java.util.*;
import java.math.BigInteger;
import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
public class kek
{
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        long a = sc.nextLong();
        long b = sc.nextLong();
        long c = sc.nextLong();
        long d = sc.nextLong();
        BigDecimal e = new BigDecimal(a);
        e = e.multiply(new BigDecimal(d));
        BigDecimal f = new BigDecimal(c);
        f = f.multiply(new BigDecimal(b));
        if (e.compareTo(f) == 1) {
            System.out.println(new String("Sasha"));
        } else if (e.compareTo(f) == 0) {
             System.out.println(new String("SashaAndKolya"));
        } else {
            System.out.println(new String("Kolya"));
        }
    }
}
/**
 * Description: Petr template
 */
import java.io.OutputStream; import java.io.IOException;
import java.io.InputStream; import java.io.PrintWriter;
import java.util.StringTokenizer; import java.util.*; 
import java.io.IOException; import java.io.BufferedReader;
import java.io.InputStreamReader; import java.io.InputStream;
//Long arithmetics
import java.math.BigInteger; import java.math.BigDecimal;
//Math
import java.math.MathContext; import java.math.RoundingMode;

public class Main {
    public static void main(String[] args) {
        //Simple input/output
        Scanner sc = new Scanner(System.in);
        long a = sc.nextLong();
        System.out.println(new String("MEX"));

        //BigDecimal
        BigDecimal e = new BigDecimal(a);
        e = e.multiply(new BigDecimal(a));
        System.out.println(e);

        //Vector, initial capacity 4
        Vector<String> vec = new Vector<String>(4);

        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Taska solver = new Taska();
        solver.solve(1, in, out);
        out.close();
    }
    static class Taska {
        int[][] array2d;
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] a = new int[n];
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                a[i] = in.nextInt();
                sum += a[i];
            }
            out.println(sum);
        }
    }
    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
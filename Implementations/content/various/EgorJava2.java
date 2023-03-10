/**
 * Description: Petr template
 */


import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
//Long arithmetics
import java.math.BigInteger;
import java.math.BigDecimal;
//Math
import java.math.MathContext;
import java.math.RoundingMode;
 

public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskD solver = new TaskD();
        solver.solve(1, in, out);
        out.close();
    }
 
    static class TaskD {
        int[][] perms;
        int[][] prod;
        int unit;
        int[] interesting;
 
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int k = in.nextInt();
            perms = generate(k);
            int[] u = new int[k];
            for (int i = 0; i < k; ++i) u[i] = i;
            unit = encode(u);
            generateProd();
            int[] p = new int[n];
            for (int i = 0; i < n; ++i) {
                p[i] = readPermutation(k, in);
            }
            interesting = new int[n + 1];
            out.println(doit(p, 0, n));
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

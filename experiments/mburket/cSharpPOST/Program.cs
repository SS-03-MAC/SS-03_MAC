using System;
using System.IO;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            int contentLength = int.Parse(System.Environment.GetEnvironmentVariable("CONTENT_LENGTH"));
            byte[] input = new byte[contentLength];
            using (var stdin = Console.OpenStandardInput()) {
            int a = stdin.Read(input, 0, input.Length);
            Console.WriteLine("Content-Type:text/html;charset=utf-8\n");
            Console.WriteLine(System.Text.Encoding.UTF8.GetString(input));
            Console.WriteLine(a);
        }
    }
}
}

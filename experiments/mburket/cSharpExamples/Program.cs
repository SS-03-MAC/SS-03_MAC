using System;


namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
           string contentLength = System.Environment.GetEnvironmentVariable("HTTP_COOKIE");
           Console.WriteLine("Content-Type:text/html;charset=utf-8");
           Console.WriteLine(contentLength);
        }
    }
}

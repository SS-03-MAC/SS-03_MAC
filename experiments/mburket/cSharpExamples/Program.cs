using System;


namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
           string contentLength = System.Environment.GetEnvironmentVariable("HTTP_COOKIE");
           Console.WriteLine("Content-Type:text/html;charset=utf-8\n");
           Console.WriteLine("<html>");
           Console.WriteLine("<head>");
           Console.WriteLine("<title>Hello World</title>");
           Console.WriteLine("</head>");
           Console.WriteLine("<body>");
           Console.WriteLine("<h1>Hello World</h1>");
           Console.WriteLine("<p>Cookies: " + contentLength + "</p>");
           Console.WriteLine("<p>Cookies length: " + contentLength.Length + "</p>");
           Console.WriteLine("</body>");
           Console.WriteLine("</html>");
        }
    }
}

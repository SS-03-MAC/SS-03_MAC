using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            string requestMethod = Environment.GetEnvironmentVariable("REQUEST_METHOD");
            if (requestMethod == "GET")
            {
                // Check if id exist if yes go to get one
            } else if (requestMethod == "GET")
            {
                // Get All Here
            }
            if (requestMethod == "POST")
            {

            }
            

        }
    }
}

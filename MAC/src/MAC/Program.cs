using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Text;
using Newtonsoft.Json;
using System.Reflection;
using MAC.Models.Attributes;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
          Type t = GetTypeFromString("users");
            string contentString = string.Empty; //GetFormContentets();

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

        public static Type GetTypeFromString(string urlName)
        {
            Type[] klasses = Assembly.GetEntryAssembly().GetTypes();
            foreach (Type t in klasses)
            {
                var attributes = t.GetTypeInfo().GetCustomAttributes<UrlName>();
                foreach (UrlName urlName2 in attributes)
                {
                    if (urlName2.Url == urlName)
                    {
                        return t;
                    }
                }
            }
            return null;
        }

    }
}

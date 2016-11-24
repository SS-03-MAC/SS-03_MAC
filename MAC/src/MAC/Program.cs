using MAC.Models;
using System;
using System.Collections.Generic;
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
            System.Threading.Thread.Sleep(35000);
            Type t = GetTypeFromString("users");
            string contentString = string.Empty; //GetFormContentets();
            string requestMethod = Environment.GetEnvironmentVariable("REQUEST_METHOD");
            List<KeyValuePair<string, string>> formData = new List<KeyValuePair<string, string>>(); //SetupFormInput(contentString);
            // The Idea for model path is format model/id
            string modelPath = Environment.GetEnvironmentVariable("SCRIPT_PATH");
            string model = string.Empty;
            int id = GetIdFromModelPath(modelPath);
            if (requestMethod == "GET" && id < 0)
            {
                ProcessGetAll(model);
            }
            else if (requestMethod == "GET")
            {
                ProcessGetOne(model, id);
            }
            else if (requestMethod == "POST")
            {
                ProcessCreate(model, formData);
            }
            else if (requestMethod == "PATCH")
            {
                ProcessUpdate(model, id, formData);
            }
            else if (requestMethod == "DELETE")
            {
                ProcessDelete(model, id);
            }
        }

        private static void ProcessCreate(string model, List<KeyValuePair<string, string>> formData)
        {
            throw new NotImplementedException();
        }

        private static void ProcessUpdate(string model, int id, List<KeyValuePair<string, string>> formData)
        {
            throw new NotImplementedException();
        }

        private static void ProcessDelete(string model, int id)
        {
            throw new NotImplementedException();
        }

        private static List<KeyValuePair<string, string>> SetupFormInput(string contentString)
        {
            string[] contentStringBeforeProcesssing = contentString.Split('=');
            List<KeyValuePair<string, string>> list = new List<KeyValuePair<string, string>>();
            for (int i = 0; i < contentStringBeforeProcesssing.Length; i += 2)
            {
                list.Add(new KeyValuePair<string, string>(contentStringBeforeProcesssing[i], contentStringBeforeProcesssing[i + 1]));
            }
            return list;
        }

        private static void ProcessGetOne(string model, int id)
        {
            User u = User.Get(id);
            BasicHeaders();
            Console.WriteLine(JsonConvert.SerializeObject(u));

        }

        private static int GetIdFromModelPath(string modelPath)
        {
            int id = -1;
            string[] splitPath = modelPath.Split('/');
            if (modelPath.Contains("/") && !string.IsNullOrWhiteSpace(splitPath[1]))
            {
                id = int.Parse(splitPath[1]);
            }

            return id;
        }

        private static void ProcessGetAll(string model)
        {
            List<User> users = User.Get();
            BasicHeaders();
            Console.Write(JsonConvert.SerializeObject(users));

        }

        private static void BasicHeaders()
        {
            Console.WriteLine("HTTP/1.1 200 OK");
            Console.WriteLine("Content-Type: application/json; charset=UTF-8");
            Console.WriteLine("Content-Encoding: UTF-8");
            Console.WriteLine("");
            Console.WriteLine("");
        }

        /// <summary>
        /// The form contents from std in
        /// </summary>
        /// <returns></returns>
        private static string GetFormContentets()
        {
            int contentLength = int.Parse(Environment.GetEnvironmentVariable("CONTENT_LENGTH"));
            List<char> contents = new List<char>();
            using (Stream stdin = Console.OpenStandardInput())
            {
                byte[] buffer = new byte[2048];
                int bytes;
                while ((bytes = stdin.Read(buffer, 0, buffer.Length)) > 0)
                {
                    contents.AddRange(Encoding.UTF8.GetChars(buffer));
                }
            }

            return contents.ToString();

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

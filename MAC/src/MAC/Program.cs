using MAC.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Newtonsoft.Json;
using System.Reflection;
using MAC.Models.Attributes;
using System.Linq;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            System.Threading.Thread.Sleep(35000);
            string contentString = string.Empty; //GetFormContentets();
            string requestMethod = Environment.GetEnvironmentVariable("REQUEST_METHOD");
            List<KeyValuePair<string, string>> formData = new List<KeyValuePair<string, string>>(); //SetupFormInput(contentString);
            string modelPath = Environment.GetEnvironmentVariable("SCRIPT_PATH");
            string model = GetModelFromModelPath(modelPath);
            Type modelType = GetTypeFromString(model);
            int id = GetIdFromModelPath(modelPath);
            if (requestMethod.ToUpper() == "GET" && id < 0)
            {
                ProcessGetAll(modelType);
            }
            else if (requestMethod.ToUpper() == "GET")
            {
                ProcessGetOne(modelType, id);
            }
            else if (requestMethod.ToUpper() == "POST")
            {
                ProcessCreate(modelType, formData);
            }
            else if (requestMethod.ToUpper() == "PATCH")
            {
                ProcessUpdate(modelType, id, formData);
            }
            else if (requestMethod.ToUpper() == "DELETE")
            {
                ProcessDelete(modelType, id);
            }
        }

        private static string GetModelFromModelPath(string modelPath)
        {
            modelPath = modelPath.Remove(0, 1);
            string[] splitPath = modelPath.Split('/');
            return splitPath[0];
        }

        private static void ProcessCreate(Type model, List<KeyValuePair<string, string>> formData)
        {
            throw new NotImplementedException();
        }

        private static void ProcessUpdate(Type model, int id, List<KeyValuePair<string, string>> formData)
        {
            throw new NotImplementedException();
        }

        private static void ProcessDelete(Type model, int id)
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

        private static void ProcessGetOne(Type model, int id)
        {
            var method = model.GetMethods(BindingFlags.Public | BindingFlags.Static |
                                          BindingFlags.FlattenHierarchy).
                Where(x => x.Name == "Get").
                First(x => x.GetGenericArguments().Length == 1 && x.GetGenericArguments().
                    First() == typeof(int));
            BasicHeaders();
            Console.WriteLine(JsonConvert.SerializeObject(u));

        }

        private static int GetIdFromModelPath(string modelPath)
        {
            int id = -1;
            modelPath = modelPath.Remove(0, 1);
            string[] splitPath = modelPath.Split('/');
            if (modelPath.Contains("/") && !string.IsNullOrWhiteSpace(splitPath[1]))
            {
                id = int.Parse(splitPath[1]);
            }

            return id;
        }

        private static void ProcessGetAll(Type model)
        {
            var method = model.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.FlattenHierarchy).Where(x => x.Name == "Get").First(x => x.GetGenericArguments().Length == 0);
            dynamic objs = method.Invoke(null, new Type[0]);
            //List<dynamic> objs = (List<dynamic>)model.GetTypeInfo().GetMethod("Get", BindingFlags.Static | BindingFlags.Public | BindingFlags.FlattenHierarch).Invoke(null, new object[0]);
            BasicHeaders();
            Console.Write(JsonConvert.SerializeObject(objs));

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

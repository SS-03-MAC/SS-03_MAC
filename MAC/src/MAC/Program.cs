using MAC.Models;
using MAC.Models.Attributes;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            //System.Threading.Thread.Sleep(35000);
            string contentString = GetFormContentets();
            string requestMethod = Environment.GetEnvironmentVariable("REQUEST_METHOD");
            string modelPath = Environment.GetEnvironmentVariable("SCRIPT_PATH");
            string model = GetModelFromModelPath(modelPath);
            Type modelType = GetTypeFromString(model);
            BaseModel formData = SetupFormInput(contentString, modelType);
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
                ProcessCreate(formData);
            }
            else if (requestMethod.ToUpper() == "PATCH")
            {
                ProcessUpdate(formData, id);
            }
            else if (requestMethod.ToUpper() == "DELETE")
            {
                ProcessDelete(modelType, id);
            }
        }

        private static void ProcessGetAll(Type model)
        {
            // There might be better way to do auth
            if (model == typeof(Auth))
            {
                string token = Environment.GetEnvironmentVariable("COOKIE");
                token = token.Remove(0, 10);
                BasicHeaders();
                // TODO: This should be done better
                JsonConvert.SerializeObject(Auth.Get("token = " + token));
            }
            else
            {
                var method = model.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.FlattenHierarchy).Where(x => x.Name == "Get").First(x => x.GetParameters().Length == 0);
                dynamic objs = method.Invoke(null, new Type[0]);
                BasicHeaders();
                Console.Write(JsonConvert.SerializeObject(objs));
            }
        }

        private static void ProcessGetOne(Type model, int id)
        {
            // The Binding flags are needed get the static inheirted methods
            var method = model.GetMethods(BindingFlags.Public | BindingFlags.Static |
                                          BindingFlags.FlattenHierarchy).
                Where(x => x.Name == "Get").
                First(x => x.GetParameters().Length == 1 && x.GetParameters().First().ParameterType == typeof(int));
            BasicHeaders();
            Console.WriteLine(JsonConvert.SerializeObject(method.Invoke(null, new object[] { id })));
        }

        private static void ProcessCreate(BaseModel model)
        {
            Console.Write("HTTP/1.1 200 OK\r\n");
            Console.Write("Content-Type: application/json; charset=UTF-8\r\n");
            Console.Write("Content-Encoding: UTF-8\r\n");
            model.Save();
            Console.Write("\r\n");
            Console.Write("{\"Id\":" + model.Id + ", \"Type\": \"create\", \"Response\": \"redirect\"}\r\n\r\n");
        }

        private static void ProcessUpdate(BaseModel model, int id)
        {
            if (model.Id.Value != id)
            {
                throw new InvalidOperationException("The given Id and model's Id do not match");
            }
            model.Save();
            Console.Write(("{ \"Type\": \"create\", \"Response\": \"redirect\"}"));
        }

        private static void ProcessDelete(Type model, int id)
        {
            // The Binding flags are needed get the static inheirted methods
            var method = model.GetMethods(BindingFlags.Public | BindingFlags.Static |
                                      BindingFlags.FlattenHierarchy).
            Where(x => x.Name == "Delete").
            First(x => x.GetParameters().Length == 1 && x.GetParameters().First().ParameterType == typeof(int));
            BasicHeaders();
            Console.WriteLine(JsonConvert.SerializeObject(method.Invoke(null, new object[] { id })));
        }

        private static BaseModel SetupFormInput(string contentString, Type type)
        {
            // Where the magic happens
            return (BaseModel)JsonConvert.DeserializeObject(contentString, type);
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

        private static void BasicHeaders()
        {
            Console.Write("HTTP/1.1 200 OK\r\n");
            Console.Write("Content-Type: application/json; charset=UTF-8\r\n");
            Console.Write("Content-Encoding: UTF-8\r\n");
            Console.Write("\r\n");
        }

        /// <summary>
        /// The form contents from std in
        /// </summary>
        /// <returns></returns>
        private static string GetFormContentets()
        {
            if (string.IsNullOrWhiteSpace(Environment.GetEnvironmentVariable("CONTENT-LENGTH")))
            {
                return string.Empty;
            }
            int contentLength = int.Parse(Environment.GetEnvironmentVariable("CONTENT-LENGTH"));
            if (contentLength < 1)
            {
                return string.Empty;
            }
            List<char> contents = GetCharsFromStdIn(contentLength);
            return ListOfCharsToString(contents);
        }

        private static List<char> GetCharsFromStdIn(int contentLength)
        {
            List<char> contents = new List<char>();
            using (Stream stdin = Console.OpenStandardInput())
            {
                byte[] buffer = new byte[contentLength];
                stdin.Read(buffer, 0, buffer.Length);
                contents.AddRange(Encoding.UTF8.GetChars(buffer));
            }

            return contents;
        }

        private static string ListOfCharsToString(List<char> contents)
        {
            string result = string.Empty;
            foreach (char c in contents)
            {
                result += c;
            }

            return result;
        }

        private static Type GetTypeFromString(string urlName)
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

        private static string GetModelFromModelPath(string modelPath)
        {
            modelPath = modelPath.Remove(0, 1);
            string[] splitPath = modelPath.Split('/');
            return splitPath[0];
        }

    }
}

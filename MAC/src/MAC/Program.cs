using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace ConsoleApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            MAC.Models.User user = new MAC.Models.User();
            using (SqlConnection conn = new SqlConnection("Server=localhost;Database=MACDevlopment;Integrated Security=true"))
            {
                conn.Open();
                using(SqlCommand cmd = new SqlCommand())
                {
                    cmd.Connection = conn;
                    cmd.CommandText = "SELECT * FROM Users where Id = 1";
                    using (SqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            user = (MAC.Models.User)MAC.Models.BaseModelFactory.FillModel(typeof(MAC.Models.User), reader);
                        } 
                    }
                }
            }
            ;
            Console.WriteLine(user.ToInsertStatement().CommandText);
            Console.ReadLine();
            List<dynamic> list = new List<dynamic>();

        }
    }
}

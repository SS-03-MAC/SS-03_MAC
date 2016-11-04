using System.Data.SqlClient;

namespace MAC.Models
{
    public class Query
    {
        /// <summary>
        /// A connection string. Should be moved. Here for dev purposes
        /// </summary>
        private static string ConnectionString = "Server=localhost;Database=MACDevlopment;User Id=macdev;Password=macdev";

        /// <summary>
        /// Runs a non-query
        /// </summary>
        /// <param name="cmd">The commad to return</param>
        /// <returns0>The number of rows effected by the query</returns>
        public static int RunNonQuery(SqlCommand cmd)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                conn.Open();
                using (cmd)
                {
                    cmd.Connection = conn;
                    return cmd.ExecuteNonQuery();
                }
            }
        }


        public static int RunInsertQuery(SqlCommand cmd)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                conn.Open();
                using (cmd)
                {
                    cmd.Connection = conn;
                    return (int) cmd.ExecuteScalar();
                }
            }
        }

        /// <summary>
        /// Run the given query
        /// </summary>
        /// <param name="query">Query can be ran</param>
        /// <returns></returns>
        public static int RunNonQuery(string query)
        {
            return RunNonQuery(new SqlCommand(query));
        }

        /// <summary>
        ///  Runs the givn command 
        /// </summary>
        /// <param name="cmd"></param>
        /// <returns></returns>
        private static SqlDataReader RunQuery(SqlCommand cmd)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                using (cmd)
                {
                    cmd.Connection = conn;
                    return cmd.ExecuteReader();
                }
            }
        }

        /// <summary>
        /// Gets all records associated with the model
        /// </summary>
        /// <returns>All records in the given table name</returns>
        public static SqlDataReader Get(string tableName)
        {
            string query = "select * from " + tableName;
            SqlCommand cmd = new SqlCommand(query);
            return RunQuery(cmd);

        }

        /// <summary>
        ///  Get the recrods matching the query
        ///  
        ///  Security note:
        ///  User inpuut should be sanitized
        ///  before placing into this method. Failing to do
        ///  so can result in SQL injection
        /// </summary>
        /// <param name="query">A valid where cause</param>
        /// <returns>Record matching the query</returns>
        public static SqlDataReader Get(string tableName, string whereClause)
        {
            string query = "select * from " + tableName + " where " + whereClause;
            SqlCommand cmd = new SqlCommand(query);
            return RunQuery(cmd);
        }

        /// <summary>
        /// Get the record by id
        /// </summary>
        /// <param name="id">ID of the record</param>
        /// <returns>Record in a SqlDataReader</returns>
        public static SqlDataReader Get(string tableName, int id)
        {
            string query = "select * from " + tableName + " where Id = @Id";
            SqlCommand cmd = new SqlCommand(query);
            cmd.Parameters.AddWithValue("@Id", id);
            return RunQuery(cmd);
        }

        /// <summary>
        /// Delete record by id 
        /// </summary>
        /// <param name="id">ID to delete</param>
        /// <returns>If the record was removed</returns>
        public static bool Delete(string tableName, int id)
        {

            string command = "DELETE FROM " + tableName + " WHERE Id = @Id;";
            SqlCommand cmd = new SqlCommand(command);
            cmd.Parameters.AddWithValue("@Id", id);
            int result = RunNonQuery(cmd);

            if (result == 1 || result == 0)
            {
                return result == 1;
            }
            else if (result > 1)
            {
                throw new UnexpectedResultExpection("The database record that it deleted more than one record.");
            }
            else
            {
                throw new UnexpectedResultExpection("The database return a negative rows removed.");
            }
        }
    }
}

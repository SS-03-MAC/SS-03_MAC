using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Reflection;

/// <summary>
/// Base model that all MAC models should be dertived from
/// </summary>
namespace MAC.Models
{
    public abstract class BaseModel
    {
        /// <summary>
        /// What table is the data stored in
        /// </summary>
        protected static string TableName;

        /// <summary>
        /// A connection string. Should be moved. Here for dev purposes
        /// </summary>
        private static string ConnectionString = "Server=localhost;Database=MACDevlopment;User Id=macdev;Password=macdev";


        /// <summary>
        /// SQL Indentify column 
        /// </summary>
        /// <returns></returns>
        public long? Id { get; }

        /// <summary>
        /// Private variable for DateTime
        /// </summary>
        private DateTime _CreatedAt { get; set; }

        /// <summary>
        /// Built-in field for when the record was saved to the database
        /// </summary>
        /// <returns></returns>
        public DateTime CreatedAt
        {
            get
            {
                return _CreatedAt;
            }
        }

        /// <summary>
        /// Internal storage for Updated at
        /// </summary>
        public DateTime _UpdatedAt { get; set; }

        /// <summary>
        /// Built-in field when the record was last updated at
        /// </summary>
        /// <returns></returns>
        public DateTime UpdatedAt
        {
            get
            {
                return _UpdatedAt;
            }
        }

        /// <summary>
        ///  Blank contrustor
        /// </summary>
        public BaseModel()
        {

        }

        public BaseModel(IDataRecord reader)
        {
            PropertyInfo[] properties = GetType().GetProperties();
            foreach (PropertyInfo property in properties)
            {
                property.SetValue(this, reader[property.Name]);
            }
        }

        /// <summary>
        /// Saves the record to the database
        /// </summary>
        /// <returns></returns>
        public bool Save()
        {
            throw new NotImplementedException();
            if (!Validate())
            {
                throw new RecordNotValidException();
            }
            if (Id == null)
            {
                _CreatedAt = DateTime.Now;
                _UpdatedAt = CreatedAt;
            }
            else
            {
                _UpdatedAt = DateTime.Now;
            }
        }

        /// <summary>
        /// Vaildates the model
        /// </summary>
        /// <returns></returns>
        public bool Validate()
        {
            PropertyInfo[] properties = GetType().GetProperties();

            foreach (PropertyInfo property in properties)
            {
                    
            }
        }

        /// <summary>
        /// Gets all records associated with the model
        /// </summary>
        /// <returns>All records</returns>
        public static List<BaseModel> Get()
        {
            string query = "select * from " + TableName;
            SqlCommand cmd = new SqlCommand(query);
            SqlDataReader reader = RunQuery(cmd);
            List<BaseModel> results = new List<BaseModel>();
            while (reader.Read())
            {
                results.Add(new BaseModel((IDataRecord)reader));
            }
            return results;
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
        public static List<BaseModel> Get(string whereClause)
        {
            string query = "select * from " + TableName + " where " + whereClause;
            SqlCommand cmd = new SqlCommand(query);
            return RunQuery(cmd);
        }

        /// <summary>
        /// Get the record by id
        /// </summary>
        /// <param name="id">ID of the record</param>
        /// <returns>Record of type T</returns>
        public static BaseModel Get(long id)
        {
            string query = "select * from " + TableName + " where Id = @Id";
            SqlCommand cmd = new SqlCommand(query);
            cmd.Parameters.AddWithValue("@Id", id);
            return RunQuery(cmd);
        }

        /// <summary>
        /// Delete record by id 
        /// </summary>
        /// <param name="id">ID to delete</param>
        /// <returns>If the record was removed</returns>
        public static bool Delete(long id)
        {

            string command = "DELETE FROM " + TableName + " WHERE Id = @Id;";
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

        /// <summary>
        ///  Delete the current record
        /// </summary>
        /// <returns></returns>
        public bool Delete()
        {
            if (Id == null)
            {
                throw new InvalidOperationException("Cannot delete a record that is not saved to the database");
            }
            return Delete((long)Id);

        }

        /// <summary>
        /// Runs a non-query
        /// </summary>
        /// <param name="cmd">The commad to return</param>
        /// <returns0>The number of rows effected by the query</returns>
        private static int RunNonQuery(SqlCommand cmd)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                using (cmd)
                {
                    cmd.Connection = conn;
                    return cmd.ExecuteNonQuery();
                }
            }
        }

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

    }
}


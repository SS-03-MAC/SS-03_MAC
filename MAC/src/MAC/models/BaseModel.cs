using MAC.Models.Attributes;
using MAC.Models.Exceptions;
using MAC.Types;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Reflection;

namespace MAC.Models
{
    /// <summary>
    /// Base model that all MAC models should be dertived from
    /// </summary>
    public abstract class BaseModel<T> : BaseModel
    {
        /// <summary>
        ///  Blank contrustor
        /// </summary>
        public BaseModel()
        {

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
            return Delete(Id.Value);

        }

        /// <summary>
        /// Get all records in the database for the model
        /// </summary>
        /// <returns>All users in the table</returns>
        public static List<T> Get()
        {
            SqlDataReader reader = Query.Get(GetStaticTableName());
            return ReaderToList(reader);
        }

        private static List<T> ReaderToList(SqlDataReader reader)
        {
            List<T> result = new List<T>();
            while (reader.Read())
            {
                result.Add((T)BaseModelFactory.FillModel(typeof(T), reader));
            }
            return result;
        }

        /// <summary>
        /// Get the given record form the database
        /// </summary>
        /// <param name="id">The ID of the record to fetch</param>
        /// <returns>The record</returns>
        /// <example>
        ///  Let's say you have an user model and you want to get the user with
        ///  the id of 10. In order to that you would write the following.
        ///  <code>
        /// User u = User.get(10) 
        /// </code>
        /// </example>
        public static T Get(int id)
        {
            SqlDataReader reader = Query.Get(GetStaticTableName(), id);
            if (!reader.HasRows)
            {
                throw new RecordNotFoundException();
            }
            reader.Read();
            T result = (T)BaseModelFactory.FillModel(typeof(T), reader);
            return result;
        }

        /// <summary>
        /// Runs a query on the talbe with a given where clause
        /// </summary>
        /// <remarks>
        /// This method will blindly place the where paramter into a SQL where statement.
        /// This means that if you pass raw unflitered user input inotot where your 
        /// application will have a SQL injection vulnerability 
        /// </remarks>
        /// <param name="where">A vaild T-SQL where clause</param>
        /// <returns>The object matching the where clause</returns>
        /// <example>
        /// Let's say you have an user model and you want to find all the users
        /// whose CreatedAt is grater than 11/08/2016 You would do the following:
        /// <code>
        /// User.Get("CreatedAT > 11/08/2016 00:00:00.000")
        /// </code>
        /// </example>
        public static List<T> Get(string where)
        {
            SqlDataReader reader = Query.Get(GetStaticTableName(), where);
            return ReaderToList(reader);
        }

        /// <summary>
        /// Get the table name for the the model
        /// </summary>
        /// <returns>Table name of class as a .NET string</returns>
        private static string GetStaticTableName()
        {

            return (typeof(T).GetTypeInfo().GetCustomAttribute(typeof(TableName)) as TableName).Name;
        }


        /// <summary>
        /// Deletes the given record with the given id
        /// </summary>
        /// <param name="id">If the record was deleted</param>
        /// <returns></returns>
        public static bool Delete(int id)
        {
            return Query.Delete(GetStaticTableName(), id);
        }
    }

    public class BaseModel : IBaseModel
    {
        /// <summary>
        /// SQL Indentify column 
        /// </summary>
        /// <returns></returns>
        [DatabaseField("Id")]
        public Integer Id { get; set; }

        /// <summary>
        /// Built-in field for when the record was saved to the database
        /// </summary>
        /// <returns></returns>
        [DatabaseField("CreatedAt")]
        public Types.DateTime CreatedAt { get; set; }

        /// <summary>
        /// Built-in field when the record was last updated at
        /// </summary>
        /// <returns></returns>
        [DatabaseField("UpdatedAt")]
        public Types.DateTime UpdatedAt { get; set; }

        /// <summary>
        /// Saves the record to the database
        /// </summary>
        /// <returns>If the record was saved to the database</returns>
        public bool Save()
        {
            if (!Validate())
            {
                throw new RecordNotValidException();
            }
            if (Id == null)
            {
                CreatedAt = new Types.DateTime(System.DateTime.Now);
                UpdatedAt = CreatedAt;
                Id = new Integer(Query.RunInsertQuery(ToInsertStatement()));
                return Id.Value > 0;
            }
            else
            {
                UpdatedAt = new Types.DateTime(System.DateTime.Now);
                return Query.RunNonQuery(ToUpdateStatement()) == 1;
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
                // TODO: Finish me
            }

            return true;
        }


        /// <summary>
        /// Converts the current record to an update statement
        /// </summary>
        /// <returns></returns>
        public SqlCommand ToUpdateStatement()
        {
            string query = "UPDATE " + GetTableName() + " SET ";
            List<KeyValuePair<string, BaseType>> values = GetDatabaseFields();
            foreach (KeyValuePair<string, BaseType> kvPair in values)
            {
                if (kvPair.Key.ToLower() == "id")
                {
                    continue;
                }
                query += kvPair.Key + "=@" + kvPair.Key + ",";
            }
            query = query.Remove(query.LastIndexOf(","));
            query += " WHERE Id = " + Id.Value + ";";
            SqlCommand result = new SqlCommand(query);
            SetValues(values, result);
            return result;
        }

        /// <summary>
        /// Get the database properities of this model in a useable format
        /// </summary>
        /// <returns></returns>
        private List<KeyValuePair<string, BaseType>> GetDatabaseFields()
        {
            List<KeyValuePair<string, BaseType>> result = new List<KeyValuePair<string, BaseType>>();
            foreach (PropertyInfo property in GetType().GetProperties())
            {
                Attribute dbField = property.GetCustomAttribute(typeof(DatabaseField));
                if (dbField is DatabaseField)
                {
                    string columnName = ((DatabaseField)dbField).Name;
                    KeyValuePair<string, BaseType> value = new KeyValuePair<string, BaseType>(columnName, (BaseType)property.GetValue(this));
                    result.Add(value);
                }
            }
            return result;
        }

        /// <summary>
        /// The values for the query
        /// </summary>
        /// <param name="values">Key Value store of the values</param>
        /// <param name="result">SQL query to add them to</param>
        private static void SetValues(List<KeyValuePair<string, BaseType>> values, SqlCommand result)
        {
            foreach (KeyValuePair<string, BaseType> kvPair in values)
            {
                if (kvPair.Key.ToLower() == "id")
                {
                    continue;
                }
                object value = null;
                if (kvPair.Value != null)
                {
                    value = kvPair.Value.GetRawObject() as object;
                }
                result.Parameters.AddWithValue(kvPair.Key, value);
            }
        }

        /// <summary>
        /// Get the values for the insert query and adds then to the query
        /// </summary>
        /// <param name="query">The insert query to add the balues to </param>
        /// <param name="values">The KeyValue store that has the values</param>
        /// <returns></returns>
        private static string GetValuesForInsert(string query, List<KeyValuePair<string, BaseType>> values)
        {
            foreach (KeyValuePair<string, BaseType> key in values)
            {
                if (key.Key.ToLower() == "id")
                {
                    continue;
                }
                query += "@" + key.Key + ",";
            }
            query = query.Remove(query.LastIndexOf(','));
            return query;
        }

        /// <summary>
        /// Get the column names in comma sperated list
        /// </summary>
        /// <param name="query">The </param>
        /// <param name="values"></param>
        /// <returns></returns>
        private static string GetColumnNames(string query, List<KeyValuePair<string, BaseType>> values)
        {
            foreach (KeyValuePair<string, BaseType> key in values)
            {
                if (key.Key.ToLower() == "id")
                {
                    continue;
                }
                query += key.Key + ",";
            }
            query = query.Remove(query.LastIndexOf(','));
            return query;
        }

        /// <summary>
        /// Converts the current record to an Insert statement
        /// 
        /// This method is public for testing purposes
        /// </summary>
        /// <returns>A SQLCommand with command text as an insert statement for insert the record into the statement</returns>
        public SqlCommand ToInsertStatement()
        {
            string query = "INSERT INTO " + GetTableName();
            List<KeyValuePair<string, BaseType>> values = GetDatabaseFields();
            query += " (";
            query = GetColumnNames(query, values);
            query += ") OUTPUT INSERTED.ID VALUES(";
            query = GetValuesForInsert(query, values);
            query += ")";
            query += ";";
            SqlCommand result = new SqlCommand(query);
            SetValues(values, result);
            return result;
        }

        /// <summary>
        /// The name table returned as string
        /// </summary>
        /// <returns>Talbe name as as string</returns>
        private string GetTableName()
        {

            return (GetType().GetTypeInfo().GetCustomAttribute(typeof(TableName)) as TableName).Name;
        }
    }
}


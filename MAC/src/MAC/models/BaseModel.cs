using System;
using System.Reflection;
using MAC.Types;
using MAC.Models.Attributes;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Diagnostics;

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
                return Query.RunNonQuery(ToInsertStatement()) == 1;
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

            }

            return true;
        }


        /// <summary>
        /// Converts the current record to an update statement
        /// </summary>
        /// <returns></returns>
        public SqlCommand ToUpdateStatement()
        {
            string result = "UPDATE " + GetTableName() + " SET ";
            foreach (KeyValuePair<string, BaseType> kvPair in GetDatabaseFields())
            {
                if (kvPair.Key.ToLower() == "id")
                {
                    continue;
                }
                result += kvPair.Key + "=@" + kvPair.Key + ",";
            }
            result = result.Remove(result.LastIndexOf(","));
            result += " WHERE Id = " + Id.Value + ";";
            return new SqlCommand(result);
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
            query += ") VALUES (";
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


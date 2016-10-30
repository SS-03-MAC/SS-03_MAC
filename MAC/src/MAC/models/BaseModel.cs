using System;
using System.Reflection;
using MAC.Types;
using MAC.Models.Attributes;

namespace MAC.Models
{
    /// <summary>
    /// Base model that all MAC models should be dertived from
    /// </summary>
    public abstract class BaseModel : IBaseModel
    {
        /// <summary>
        /// What table is the data stored in
        /// </summary>
        protected static string TableName;

        /// <summary>
        /// SQL Indentify column 
        /// </summary>
        /// <returns></returns>
        [DatabaseField("ID")]
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
        ///  Blank contrustor
        /// </summary>
        public BaseModel()
        {

        }

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

            return false;
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
        /// Converts the current record to an Insert statement
        /// </summary>
        private string ToInsertStatement()
        {
            string result = "INSERT INTO " + TableName;
            result += " (";
            // Loop though fields here
            result += ") VALUES (";
            // Loop though values
            result += ")";
            result += ";";
            return result;
        }

        /// <summary>
        /// Converts the current record to an update statement
        /// </summary>
        /// <returns></returns>
        private string ToUpdateStatement()
        {
            string result = "UPDATE";
            return result;
        }

        /// <summary>
        /// Deletes the given record with the given id
        /// </summary>
        /// <param name="id">If the record was deleted</param>
        /// <returns></returns>
        public static bool Delete(int id)
        {
            return Query.Delete(TableName, id);
        }
    }
}


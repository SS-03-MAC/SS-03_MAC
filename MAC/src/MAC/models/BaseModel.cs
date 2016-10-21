using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Reflection;

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
                property.SetValue(this, reader[s]);
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

  

    }
}


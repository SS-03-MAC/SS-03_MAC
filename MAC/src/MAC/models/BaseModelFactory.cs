using System;
using System.Data;
using System.Linq;
using System.Reflection;
using MAC.Models.Attributes;


namespace MAC.Models
{
    /// <summary>
    /// This class is a factory for models
    /// </summary>
    public static class BaseModelFactory
    {
        /// <summary>
        /// This method fill a model 
        /// </summary>
        /// <param name="model">The Type of model to create</param>
        /// <param name="reader">The row that represnets the model</param>
        /// <returns>The filled model as an object</returns>
        public static object FillModel(Type model, IDataRecord reader)
        {
            // Create an instance of the model
            var output = Activator.CreateInstance(model);
            // Get the properties of the model
            var properties = output.GetType().GetProperties();
            foreach (PropertyInfo property in properties)
            {
                // Check if the property has a DatabaseField attribute
                Attribute dbField = property.GetCustomAttribute(typeof(DatabaseField));
                if (dbField is DatabaseField)
                {
                    // Start to fill the model
                    DatabaseField databaseField = (DatabaseField)property.GetCustomAttributes(typeof(DatabaseField)).FirstOrDefault();
                    Type dataType = reader.GetFieldType(reader.GetOrdinal(databaseField.Name));
                    var data = reader[databaseField.Name];
                    // Make the type
                    Type[] constructorInfo = new Type[1];
                    constructorInfo[0] = dataType;
                    ConstructorInfo valueConstructor = property.PropertyType.GetConstructor(constructorInfo);
                    object[] contrustorArgs = new object[1];
                    contrustorArgs[0] = data;
                    // Set the value
                    property.SetValue(output, valueConstructor.Invoke(contrustorArgs));
                }
            }
            return output;
        }
    }
}

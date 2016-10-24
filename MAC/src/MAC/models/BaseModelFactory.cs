﻿using System;
using System.Data;
using System.Linq;
using System.Reflection;
using MAC.Models.Attributes;


namespace MAC.Models
{
    public static class BaseModelFactory
    {
        public static object FillModel(Type model, IDataRecord reader)
        {
            var output = Activator.CreateInstance(model);
            var properties = output.GetType().GetProperties();
            foreach (PropertyInfo property in properties)
            {
                Attribute dbField = property.GetCustomAttribute(Type.GetType("DatabaseField"));
                if (dbField is DatabaseField)
                {
                    DatabaseField databaseField = (DatabaseField)property.GetCustomAttributes(typeof(DatabaseField)).FirstOrDefault();
                    Type dataType = reader.GetFieldType(reader.GetOrdinal(databaseField.Name));
                    var data = reader[databaseField.Name];
                    Type[] constructorInfo = new Type[1];
                    constructorInfo[1] = dataType;
                    ConstructorInfo valueConstructor = dataType.GetConstructor(constructorInfo);
                    object[] contrustorArgs = new object[1];
                    contrustorArgs[0] = data;
                    property.SetValue(output, valueConstructor.Invoke(contrustorArgs));
                }
            }
            return output;
        }
    }
}

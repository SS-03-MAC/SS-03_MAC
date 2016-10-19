using System;
using System.Collections.Generic;

/// <summary>
/// Base model that all MAC models should be dertived from
/// </summary>
public abstract class BaseModel {
  /// <summary>
  /// What table is the data stored in
  /// </summary>
  private string TableName;

  /// <summary>
  /// SQL Indentify column 
  /// </summary>
  /// <returns></returns>
  public long Id { get; }

  /// <summary>
  /// Built-in field for when the record was saved to the database
  /// </summary>
  /// <returns></returns>
  public DateTime CreatedAt { get; set; }
  /// <summary>
  /// Built-in field when the record was last updated at
  /// </summary>
  /// <returns></returns>
  public DateTime UpdatedAt { get; }

  /// <summary>
  ///  Blank contrustor
  /// </summary>
  public BaseModel() {

  }

  /// <summary>
  /// Saves the record to the database
  /// </summary>
  /// <returns></returns>
  public bool Save() {
    if (id == null) {
      CreatedAt = Time.now.utc
      UpdatedAt = CreatedAt
    } else {
      UpdatedAt = Time.now.utc
    }
  }

  /// <summary>
  /// Vaildates the model
  /// </summary>
  /// <returns></returns>
  public abstract bool Validates();

  /// <summary>
  /// Gets all records associated with the model
  /// </summary>
  /// <returns>All records</returns>
  public static List<T> Get() {
    throw new NotImplementedException();
  }
 
  /// <summary>
  ///  Get the recrods matching the query
  /// </summary>
  /// <param name="query">A valid where cause</param>
  /// <returns>Record matching the query</returns>
  public static List<T> Get(string query) {
    throw new NotImplementedException();
  }

  /// <summary>
  /// Get the record by id
  /// </summary>
  /// <param name="id">ID of the record</param>
  /// <returns>Record of type T</returns>
  public static T Get(long id) {
    throw new NotImplementedException();
  }

 /// <summary>
  /// Delete record by id 
  /// </summary>
  /// <param name="id">ID to delete</param>
  /// <returns>If the record was removed</returns>
  public static bool Delete(long id) {
    throw new NotImplementedException();
  }

  /// <summary>
  ///  Delete the current record
  /// </summary>
  /// <returns></returns>
  public bool Delete() {
    throw new NotImplementedException();
  }

}

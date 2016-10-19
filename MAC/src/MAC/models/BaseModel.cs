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
  /// SQL Indentify colimn 
  /// </summary>
  /// <returns></returns>
  public long Id { get; }

  /// <summary>
  ///  Blank
  /// </summary>
  public BaseModel() {

  }

  /// <summary>
  /// Saves the record to the database
  /// </summary>
  /// <returns></returns>
  public abstract bool Save();


  /// <summary>
  /// Vaildates the model
  /// </summary>
  /// <returns></returns>
  public abstract bool Validates();


  /// <summary>
  /// Gets all records associated with the model
  /// </summary>
  /// <returns>All records</returns>
  public List<T> Get() {
    throw new NotImplementedException();
  }
 
  /// <summary>
  ///  Get the recrods matching the query
  /// </summary>
  /// <param name="query">A valid where cause</param>
  /// <returns>Record matching the query</returns>
  public List<T> Get(string query) {
    throw new NotImplementedException();
  }

  /// <summary>
  /// Get the record by id
  /// </summary>
  /// <param name="id">ID of the record</param>
  /// <returns>Record of type T</returns>
  public T Get(long id) {
    throw new NotImplementedException();
  }
}

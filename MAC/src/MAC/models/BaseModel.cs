public abstract class BaseModel {
  private string TableName;

  public long Id { get; }

  public BaseModel() {

  }

  public bool Save();

  public bool Update();
}

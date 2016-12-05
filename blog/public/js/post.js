var Post = function(Title, Body, PublishedAt){
  this.Title = Title;
  this.Body = Body;
  this.PublishedAt = PublishedAt;
  this.id = 0;
  this.CreatedAt = Date.now();
  this.UpdatedAt = Date.now();

  this.save = function(path, success, failure){
    var xhr = new XMLHttpRequest();
    if(this.id == 0){
      xhr.open("POST", path + "/posts/", true);
    } else{
      xhr.open("PATCH", path + "/posts/"+this.id);
    }

    xhr.setRequestHeader("Content-type", "application/json");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){

          if (success !== undefined) {
            success(xhr);
          }

          console.log(xhr.responseText);
        } else{

          if (failure !== undefined) {
            failure(xhr);
          }
          throw new Error(xhr.statusText);
        }
      }
    };

    var data = JSON.stringify(this);
    xhr.send(data);
  };

  this.delete = function(path, success, failure){
    if(this.id == 0){
      return; //never saved to database, don't have to do anything
    }

    var xhr = new XMLHttpRequest();
    xhr.open("DELETE", path + "/posts/"+this.id, true);
    xhr.setRequestHeader("Content-type", "application/json");
    xhr.onreadystatechange = function() {
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          console.log(xhr.responseText);

          if (success !== undefined) {
            success(xhr);
          }

        } else{

          if (failure !== undefined) {
            failure(xhr);
          }

          throw new Error(xhr.statusText);
        }
      }
    };

    xhr.send(null);
  };




};

Post.get = function(id, ret, path, success, failure){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Title", "Body", "PublishedAt"];
        var result = JSON.parse(xhr.responseText);

        for(var field in result){
          if(fields.indexOf(field) !== -1){
            ret[field] = result[field];
          }
        }

        if (success !== undefined) {
          success(xhr);
        }

      } else{

        if (failure !== undefined) {
          failure(xhr);
        }

        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", path + "/posts/"+id, true);
  xhr.send(null);
};

Post.getAll = function(arr, path, success){
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var fields = ["id", "CreatedAt", "UpdatedAt", "Title", "Body", "PublishedAt"];
        var result = JSON.parse(xhr.responseText);

        for(var i = 0; i < result.length; i++){
          tmp = new Post();
          obj = result[i];
          for(var field in obj){
            if(fields.indexOf(field) !== -1){
              tmp[field] = obj[field];
            }
          }

          arr.push(tmp);
        }

        if (success !== undefined) {
          success(xhr);
        }
      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", path + "/posts", true);
  xhr.send(null);
};

# MAC Built in Tables
## Users
- Id
- Email
- PasswordHash
- CreatedAt
- UpdatedAt

## Sessions
- Id
- UserId
- CreatedAt
- UpdatedAt

## Roles
- Id
- Name
- CreatedAt
- UpdatedAt


## RoleMembership
- Id
- RoleId
- UserId
- CreatedAt
- UpdatedAt

## Models
- Id
- Name


## Attributes
- Id
- ModelId

## ACL
- Id
- AttributeId
- Level
  - Read
  - Write
  - Admin (Full Access)

using UnitTestDemo;
using Xunit;
using Moq;
using System;

namespace XUnitTestProject
{
    [Collection("Database collection")]
    public class UserManagerTest //: IClassFixture<DatabaseFixture>
    {
        /*public UserManagerTest()
        {
            using (var dbContext = new UserDbContext())
            {
                dbContext.Database.EnsureDeleted();
                dbContext.Database.EnsureCreated();
            }
        }*/

        [Fact]
        public void CreateUserWithExceptionTest()
        {
            var mockObject = new Mock<IUserRepository>();
            var user = new User() { Name = "selim", Age = -1 };
            mockObject.Setup(repository => repository.Add(user)).Returns(true);

            var userManager = new UserManager(mockObject.Object);
            Assert.Throws<FormatException>(() => userManager.CreateNewUser(user));
        }

        [Fact]
        public void CreateUserTest()
        {
            var mockObject = new Mock<IUserRepository>();
            var user = new User() { Name = "selim", Age = 1 };
            mockObject.Setup(repository => repository.Add(user)).Returns(true);
            var userManager = new UserManager(mockObject.Object);
            var result = userManager.CreateNewUser(user);
            Assert.True(result);
        }

        [Fact]
        public void CreateUserWithDBTest()
        {
            var repository = new SqlServerUserRepository();
            var user = new User() { Name = "selim", Age = 1 };
            var userManager = new UserManager(repository);
            var result = userManager.CreateNewUser(user);
            Assert.True(result);
            var u = userManager.GetUserByName("selim");
            Assert.Equal(user.Name, u.Name);
            Assert.Equal(user.Age, u.Age);
            var count = userManager.GetAllUserCount();
            Assert.Equal(3, count);
        }
    }
}

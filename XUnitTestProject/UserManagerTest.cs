using UnitTestDemo;
using Xunit;
using Moq;
using System;

namespace XUnitTestProject
{
    public class UserManagerTest
    {
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
    }
}

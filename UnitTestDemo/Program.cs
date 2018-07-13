using System;
using System.Collections.Generic;
using System.Data;
using System.IO;

namespace UnitTestDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            var cal = new Calculator();
            var result = cal.Addition(1, 2);
            var repository = new SqlServerUserRepository();
            var user = new User() { Name = "selim", Age = 1 };
            var userManager = new UserManager(repository);
            userManager.CreateNewUser(user);
            var u = userManager.GetUserByName("selim");
        }
    }
}

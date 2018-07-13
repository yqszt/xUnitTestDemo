using System;
using System.Collections.Generic;
using System.Text;

namespace UnitTestDemo
{
    public class User
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Age { get; set; }
    }

    public interface IUserRepository
    {
        bool Add(User user);
        int Count();
        User GetByName(string name);
    }

    public class UserManager
    {
        private IUserRepository userRepository;

        public UserManager(IUserRepository userRepository)
        {
            this.userRepository = userRepository;
        }

        public bool CreateNewUser(User user)
        {
            if (user.Age < 0 || string.IsNullOrEmpty(user.Name))
            {
                throw new FormatException("Age or Name is invalid.");
            }
            else
            {
               return this.userRepository.Add(user);
            }
        }

        public User GetUserByName(string name)
        {
            return this.userRepository.GetByName(name);
        }

        public int GetAllUserCount()
        {
            return this.userRepository.Count();
        }
    }
}

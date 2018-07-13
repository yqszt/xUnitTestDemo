using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UnitTestDemo
{
    public class SqlServerUserRepository : IUserRepository
    {
        public bool Add(User user)
        {
            using (var db = new UserDbContext())
            {
                db.Add(user);
                var rows = db.SaveChanges();
                if (rows > 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        public int Count()
        {
            using (var db = new UserDbContext())
            {
                return db.Users.Count();
            }
        }

        public User GetByName(string name)
        {
            using (var db = new UserDbContext())
            {
                return db.Users.Where(u => u.Name.Equals(name)).FirstOrDefault();
            }
        }
    }
}

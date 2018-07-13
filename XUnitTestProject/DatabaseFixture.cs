using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UnitTestDemo;

namespace XUnitTestProject
{
    public class DatabaseFixture : IDisposable
    {
        public DatabaseFixture()
        {
            using (var dbContext = new UserDbContext())
            {
                dbContext.Database.EnsureDeleted();
                dbContext.Database.EnsureCreated();
                var sqlFiles = Directory.GetFiles(@"Data", "*.sql");
                foreach (var file in sqlFiles)
                {
                    dbContext.Database.ExecuteSqlCommand(File.ReadAllText(file));
                }
            }
        }

        public void Dispose()
        {
            using (var dbContext = new UserDbContext())
            {
                dbContext.Database.EnsureDeleted();
            }
        }
    }

}

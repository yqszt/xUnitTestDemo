using System;
using System.Collections.Generic;
using System.Text;
using Xunit;

namespace XUnitTestProject
{
    [CollectionDefinition("Database collection")]
    public class DatabaseCollection : ICollectionFixture<DatabaseFixture>
    {
    }
}

OpenCover.Console.exe -target:"dotnet.exe" -targetargs:"test" -output:coverage.xml -register:user -filter:"+[*]* -[*Moq]*  -[xunit*]*" -oldstyle

ReportGenerator.exe "-reports:coverage.xml" "-targetdir:report"
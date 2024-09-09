with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;
procedure oldcal is
    --  Determine if a year is valid
    function isvalid(year: Integer) return Boolean is
    begin
        --  Determine if year is within Gregorian calendar range
        if year >= 1582 then
            return True;
        else
            return False;
        end if;
    end isvalid;

    --  Get the year and language from user and calculate the first day of the year
    procedure readcalinfo(year: out Integer; firstday: out Integer; lang: out Character) is
        userLanguageCheck: Boolean;
        y: Integer;
    begin
        --  Get and validate year from user
        year := 0;

        while not isvalid(year) loop
            put("Enter the year: ");
            get(year);

            if not isvalid(year) then
                put_line("Invalid year. Please try again.");
            end if;
        end loop;

        --  Get and validate preferred language from user
        userLanguageCheck := False;

        while not userLanguageCheck loop
            put("Enter your preferred language (E=english/F=french): ");
            get(lang);
            skip_line;

            if lang /= 'E' and lang /= 'F' then
                put_line("Invalid entry (must enter E or F). Please try again.");
            else
                userLanguageCheck := True;
            end if;
        end loop;

        --  Calculate the first day of the year
        y := year - 1;
        firstday := (36 + y + (y / 4) - (y / 100) + (y / 400)) mod 7;
    end readcalinfo;

    --  Determine if its a leap year
    function leapyear(year: Integer) return Boolean is
    begin
        -- Check if its a leap year
        if year mod 400 = 0 then
            return True;
        elsif year mod 100 = 0 then
            return False;
        elsif year mod 4 = 0 then
            return True;
        else
            return False;
        end if;
    end leapyear;

    --  Determine the number of days in a given month
    function numdaysinmonth(month: Integer; year: Integer) return Integer is
    begin
        --  Determine the number of days
        if month = 1 or month = 3 or month = 5 or month = 7 or month = 8 or month = 10 or month = 12 then
            return 31;
        elsif month = 2 and leapyear(year) then
            return 29;
        elsif month = 2 then
            return 28;
        else
            return 30;
        end if;
    end numdaysinmonth;

    --  Print month and week headings for a given row and language
    procedure printrowheading(row: in Integer; lang: in Character) is
    begin
        --  Print the months for the correct language
        if lang = 'E' then
            --  Print the months for the correct row
            if row = 1 then
                put("      January         ");
                put("      February        ");
                put("       March        ");
            elsif row = 2 then
                put("       April          ");
                put("        May           ");
                put("        June        ");
            elsif row = 3 then
                put("        July          ");
                put("       August         ");
                put("     September      ");
            elsif row = 4 then
                put("      October         ");
                put("      November        ");
                put("      December      ");
            end if;
        elsif lang='F' then
            --  Print the months for the correct row
            if row = 1 then
                put("      Janvier         ");
                put("      Fevrier         ");
                put("        Mars        ");
            elsif row = 2 then
                put("       Avril          ");
                put("        Mai           ");
                put("        Juin        ");
            elsif row = 3 then
                put("      Juillet         ");
                put("        Aout          ");
                put("     Septembre      ");
            elsif row = 4 then
                put("      Octobre         ");
                put("      Novembre        ");
                put("      Decembre      ");
            end if;
        end if;

        --  Print the days of the week
        new_line;
        for i in 1..3 loop
            put("Su Mo Tu We Th Fr Sa");
            
            if (i /= 3) then
                put("  ");
            end if;
        end loop;
        new_line;
    end printrowheading;

    --  Print the dates of the months
    procedure printrowmonth(row: in Integer; firstday: in out Integer; year: in Integer) is
        month, countDays, maxDays: Integer;
        month1, month2, month3: array(1..6, 1..7) of Integer;
    begin
        --  Initialize arrays to 0
        for i in 1..6 loop
            for j in 1..7 loop
                month1(i,j) := 0;
                month2(i,j) := 0;
                month3(i,j) := 0;
            end loop;
        end loop;

        --  Determine starting month
        if row = 1 then
            month := 1;
        elsif row = 2 then
            month := 4;
        elsif row = 3 then
            month := 7;
        elsif row = 4 then
            month := 10;
        end if;

        --  Store dates for correct row in arrays
        for k in 1..3 loop
            --  Set initial values
            maxDays := numdaysinmonth(month,year);
            countDays := 1;

            --  Set dates
            for i in 1..6 loop
                for j in 1..7 loop
                    --  Start at first day
                    if (i/=1 or j>firstday) and countDays <= maxDays then
                        --  Set for correct month
                        if month = 1 or month = 4 or month = 7 or month = 10 then
                            month1(i,j) := countDays;
                        elsif month = 2 or month = 5 or month = 8 or month = 11 then
                            month2(i,j) := countDays;
                        elsif month = 3 or month = 6 or month = 9 or month = 12 then
                            month3(i,j) := countDays;
                        end if;

                        --  Update values to count days
                        countDays := countDays + 1;
                        firstday := firstday + 1;
                    end if;
                end loop;

                --  Keep track of the first day
                if countDays <= maxDays then
                    firstday := 0;
                end if;
            end loop;

            --  Update values
            month := month + 1;

            if firstday = 7 then
                firstday := 0;
            end if;
        end loop;

        --  Print dates for each month
        for i in 1..6 loop
            for j in 1..7 loop
                if (month1(i,j) = 0) then
                    put("  ");
                else
                    put(month1(i,j),width => 2);
                end if;
                put(" ");
            end loop;
            put(" ");

            for j in 1..7 loop
                if (month2(i,j) = 0) then
                    put("  ");
                else
                    put(month2(i,j),width => 2);
                end if;
                put(" ");
            end loop;
            put(" ");

            for j in 1..7 loop
                if (month3(i,j) = 0) then
                    put("  ");
                else
                    put(month3(i,j),width => 2);
                end if;
                put(" ");
            end loop;
            new_line;
        end loop;
        new_line;
    end printrowmonth;
    
    --  Print year banner
    procedure banner(year: in Integer; indent: in Integer) is
        infp: File_Type;
        fileContent: String(1..7);
        fileLine: Integer;
        yearDigits: array(1..4) of Integer;
        subtype line is String(1..7);
        number1, number2, number3, number4: array(1..10) of line;
    begin
        --  Open file
        open(infp,in_file,"alphabet.txt");

        --  Separate digits of the year
        yearDigits(1) := year / 1000;
        yearDigits(2) := (year mod 1000) / 100;
        yearDigits(3) := (year mod 100) / 10;
        yearDigits(4) := year mod 10;

        --  Get digits from file
        for i in 1..4 loop
            fileLine := 1;

            loop
                --  Read through whole file
                exit when end_of_file(infp);

                --  Store the correct digit
                if fileLine = yearDigits(i)*10+1 then
                    for j in 1..10 loop
                        get(infp,fileContent);

                        --  Store in the correct variable
                        if i=1 then
                            number1(j) := fileContent;
                        elsif i=2 then
                            number2(j) := fileContent;
                        elsif i=3 then
                            number3(j) := fileContent;
                        elsif i=4 then
                            number4(j) := fileContent;
                        end if;

                        fileLine := fileLine + 1;
                    end loop;
                else
                    get(infp,fileContent);
                    fileLine := fileLine + 1;
                end if;
            end loop;

            --  Reset to the start of the file
            reset(infp);
        end loop;

        --  Print year
        for i in 1..10 loop
            --  Print indent for numbers
            for i in 1..indent loop
                put(" ");
            end loop;

            --  Print numbers
            put(number1(i));
            put("  ");
            put(number2(i));
            put("  ");
            put(number3(i));
            put("  ");
            put(number4(i));
            new_line;
        end loop;
        
        --  Close file
        close(infp);
    end banner;

    --  Build calendar
    procedure buildcalendar is
        year, firstday: Integer;
        language: Character;
    begin
        --  Get information from user
        readcalinfo(year, firstday, language);

        --  Print banner
        banner(year,15);
        new_line;

        --  Print calendar
        for i in 1..4 loop
            printrowheading(i,language);
            printrowmonth(i,firstday,year);
        end loop;
    end buildcalendar;

begin
    --  Call function to create calendar
    buildcalendar;
    
end oldcal;
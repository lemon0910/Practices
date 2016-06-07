local file = io.open("file.txt", "w")
local t = {}
for i = 1, 500000000 do
        local n = i % math.random(10000)
        local str = string.format("This is a number %d\n", n)
        table.insert(t, str)
        if i % 10000 == 0 then
                file:write(table.concat(t))
                t = {}
        end
end

import Data.Text (Text)
import qualified Data.Text as T
import qualified Data.Text.IO as TIO
import Foreign
import Foreign.C.Types
import Foreign.C.String

data StructType
    = Array
    | LinkedList
    | DoubleList
    | HashTable
    deriving (Show)

data Token
    = TInt Int
    | TNull
    | TPair Int Int
    deriving (Show)

data ParsedStruct = ParsedStruct
    { structType :: StructType
    , structData :: [[Token]] }

data ParseError
    = ErrSyntax
    | ErrSemantics

-- Parses a formatted 'String' or returns a parsing error
parse :: Text -> Either ParseError [ParsedStruct]
parse str =
    let blocks = splitBlocks (T.lines str)
    in traverse parseBlock blocks

splitBlock :: [Text] -> [[Text]]
splitBlock str =
    let items 

-- The function exposes to C 
foreign export ccall parseFile :: CString -> IO (Ptr CString)

parseFile :: CString -> IO (Ptr CString)
parseFile path = do
    contents <- peekCString path >>= TIO.readFile
    case parse contents of
        Left err        -> newCString ("Error: " ++ show err)
        Right structs   -> newCString (serialize structs)


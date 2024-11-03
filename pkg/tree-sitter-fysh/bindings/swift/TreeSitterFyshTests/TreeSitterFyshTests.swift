import XCTest
import SwiftTreeSitter
import TreeSitterFysh

final class TreeSitterFyshTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_fysh())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Fysh grammar")
    }
}

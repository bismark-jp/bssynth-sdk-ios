//
//  ViewController.swift
//  sample2
//
//  Copyright © 2020 bismark LLC. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    private let channel = UInt8(0)
    private var program = UInt8(0)
    private let velocity = UInt8(127)

    @IBOutlet weak var programChangeStepper: UIStepper!
    @IBOutlet weak var programChangeLabel: UILabel!

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        let program = UInt8(self.programChangeStepper.value + 0.5)
        BssynthDriver.shared.setChannnelMessage(status: 0xC0 + channel, data1: program, data2: 0x00)
        updateProgramChange()
    }

    @IBAction func noteOn(_ sender: UIButton) {
        let note = 0x3C + UInt8(sender.tag)
        BssynthDriver.shared.setChannnelMessage(status: 0x90 + channel, data1: note, data2: velocity)
    }

    @IBAction func noteOff(_ sender: UIButton) {
        let note = 0x3C + UInt8(sender.tag)
        BssynthDriver.shared.setChannnelMessage(status: 0x90 + channel, data1: note, data2: 0x00)
    }
    
    @IBAction func programChange(_ sender: UIStepper) {
        let program = UInt8(sender.value + 0.5)
        BssynthDriver.shared.setChannnelMessage(status: 0xC0 + channel, data1: program, data2: 0x00)
        updateProgramChange()
    }
    
    private func updateProgramChange() {
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.15) { [weak self] in
            guard let `self` = self else { return }
            self.programChangeLabel.text = BssynthDriver.shared.currentProgramName(channel: self.channel)
        }
    }

}
